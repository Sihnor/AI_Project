// Copyright Epic Games, Inc. All Rights Reserved.

#include "AI_ProjectCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Actors/Resource.h"
#include "DrawDebugHelpers.h"

#define ECC_Resource		ECC_GameTraceChannel1

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AAI_ProjectCharacter

AAI_ProjectCharacter::AAI_ProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	this->bUseControllerRotationPitch = false;
	this->bUseControllerRotationYaw = false;
	this->bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	this->CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	this->CameraBoom->SetupAttachment(RootComponent);
	this->CameraBoom->TargetArmLength = 1000.0f; // The camera follows at this distance behind the character
	this->CameraBoom->SocketOffset = FVector(600.f, 0.f, 600.f);
	this->CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	this->FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	this->FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	this->FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	this->FollowCamera->SetRelativeRotation(FRotator(0.f, 320.f, 0.f));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AAI_ProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input
void AAI_ProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(this->JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(this->JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(this->MoveAction, ETriggerEvent::Triggered, this, &AAI_ProjectCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(this->LookAction, ETriggerEvent::Triggered, this, &AAI_ProjectCharacter::Look);

		EnhancedInputComponent->BindAction(this->CommandNPCAction, ETriggerEvent::Started, this, &AAI_ProjectCharacter::CommandNPC);

		EnhancedInputComponent->BindAction(this->SummonNPCAction, ETriggerEvent::Started, this, &AAI_ProjectCharacter::SummonNPC);
	}
}

void AAI_ProjectCharacter::Move(const FInputActionValue& Value)
{
	if (Controller == nullptr) return;

	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	// find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// add movement 
	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AAI_ProjectCharacter::Look(const FInputActionValue& Value)
{
	if (Controller == nullptr) return;
	
	const FVector2D lookAxisVector = Value.Get<FVector2D>();

	// add yaw and pitch input to controller
	AddControllerYawInput(lookAxisVector.X);
	//AddControllerPitchInput(LookAxisVector.Y);
}

void AAI_ProjectCharacter::CommandNPC(const FInputActionValue& Value)
{
	const FVector start = this->GetActorLocation()  + this->GetActorForwardVector() * this->SummonDistance;
	const FVector end = start + this->GetActorForwardVector() * this->SummonDistance;
	const FCollisionShape boxCollision = FCollisionShape::MakeBox(FVector(this->SummonDistance, 200, 50));
	TArray<FHitResult> hitResults;
	
	const FQuat rotation = FQuat::FindBetween(FVector::ForwardVector, GetActorForwardVector());


	DrawDebugLine(GetWorld(), start, end, FColor::Purple, false, 1.0f);
	DrawDebugBox(GetWorld(), start, boxCollision.GetBox(), rotation, FColor::Purple, false, 1.0f);
	
	//DrawDebugBox(GetWorld(), start, boxCollision.GetBox(), rotation, FColor::Purple, false, 5.0f);
	const bool isHit = GetWorld()->SweepMultiByChannel(hitResults, start, start, rotation, ECC_Resource, boxCollision);

	
	if (!isHit)return;

	FCollisionShape sphereCollision = FCollisionShape::MakeSphere(50);
	
	FVector hitLocation = FVector::Zero();

	for (FHitResult HitResult : hitResults)
	{
		// First location save
		if (hitLocation == FVector::Zero())
		{
			hitLocation = HitResult.Location;
		}
		
		if (HitResult.Location.SquaredLength() < hitLocation.SquaredLength())
		{
			hitLocation = HitResult.Location;
		}
		//DrawDebugSphere(GetWorld(), HitResult.Location, 50, 10, FColor::Red, false, 5.0f);
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Hit: %s"), *(HitResult.GetActor()->GetName())));
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Hit: %s"), *(HitResult.GetActor()->GetActorLocation().ToString())));
	}
	
	
}

void AAI_ProjectCharacter::SummonNPC(const FInputActionValue& Value)
{
	return;
}
