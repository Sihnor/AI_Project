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
#include "DrawDebugHelpers.h"
#include "Actors/Stone.h"
#include "Actors/Tree.h"

#define ECC_Resource		ECC_GameTraceChannel1
#define ECC_NPC				ECC_GameTraceChannel2

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AAI_ProjectCharacter

AAI_ProjectCharacter::AAI_ProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	this->bUseControllerRotationPitch = false;
	this->bUseControllerRotationYaw = false;
	this->bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; 	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	this->CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	this->CameraBoom->SetupAttachment(RootComponent);
	this->CameraBoom->TargetArmLength = 1000.0f;
	this->CameraBoom->SocketOffset = FVector(600.f, 0.f, 600.f);
	this->CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	this->FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	this->FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	this->FollowCamera->bUsePawnControlRotation = false;
	this->FollowCamera->SetRelativeRotation(FRotator(0.f, 320.f, 0.f));
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

		EnhancedInputComponent->BindAction(this->CommandNPCAction, ETriggerEvent::Triggered, this, &AAI_ProjectCharacter::CommandNPC);

		EnhancedInputComponent->BindAction(this->SummonNPCAction, ETriggerEvent::Triggered, this, &AAI_ProjectCharacter::SummonNPC);
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

	AddControllerYawInput(lookAxisVector.X);
	//AddControllerPitchInput(LookAxisVector.Y);
}

void AAI_ProjectCharacter::CommandNPC(const FInputActionValue& Value)
{
	FHitResult hitResults;
	
	const bool bIsHit = GetClosestResource(hitResults);
	if (!bIsHit)return;

	TArray<FHitResult> hitResultsInSphere = this->GetSameResourceTypeInSphere(hitResults.GetActor());
	
	for (auto HitResult : hitResultsInSphere)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Hit: %s"), *(HitResult.GetActor()->GetName())));
	}
}

bool AAI_ProjectCharacter::GetAllResourcesInBox(TArray<FHitResult>& result)
{
	const FVector start = this->GetActorLocation() + this->GetActorForwardVector() * this->SummonDistance;
	const FVector end = start + this->GetActorForwardVector() * this->SummonDistance;
	const FCollisionShape boxCollision = FCollisionShape::MakeBox(FVector(this->SummonDistance, 200, 50));
	
	const FQuat rotation = FQuat::FindBetween(FVector::ForwardVector, GetActorForwardVector());

	DrawDebugBox(GetWorld(), start, boxCollision.GetBox(), rotation, FColor::Purple, false, 1.0f);

	return GetWorld()->SweepMultiByChannel(result, start, start, rotation, ECC_Resource, boxCollision);
}

bool AAI_ProjectCharacter::GetClosestResource(FHitResult& results)
{
	const FVector start = this->GetActorLocation() + this->GetActorForwardVector() * this->SummonDistance;
	const FCollisionShape boxCollision = FCollisionShape::MakeBox(FVector(this->SummonDistance, 200, 50));

	TArray<FHitResult> hitResults;
	bool bIsHit = GetAllResourcesInBox(hitResults);

	FVector hitLocation = FVector::Zero();
	
	for (FHitResult hitResult : hitResults)
	{
		// First location save
		if (hitLocation == FVector::Zero())
		{
			results = hitResult;
			hitLocation = hitResult.GetActor()->GetActorLocation();
		}
		
		if ((hitResult.GetActor()->GetActorLocation() - this->GetActorLocation()).SquaredLength() <
			(hitLocation - this->GetActorLocation()).SquaredLength())
		{
			results = hitResult;
			hitLocation = hitResult.GetActor()->GetActorLocation();
		}
	}

	return bIsHit;
}

TArray<FHitResult> AAI_ProjectCharacter::GetSameResourceTypeInSphere(const AActor* const closestResource)
{
	TArray<FHitResult> hitResults;
	GetWorld()->SweepMultiByChannel(hitResults, closestResource->GetActorLocation(), closestResource->GetActorLocation(), FQuat::Identity, ECC_Resource, FCollisionShape::MakeSphere(this->SphereRadius));
	DrawDebugSphere(GetWorld(), closestResource->GetActorLocation(), this->SphereRadius, 10, FColor::Green, false, 1.0f);

	TArray<FHitResult> sameResourceTypeInSphere;

	for (auto hitResult : hitResults)
	{
		// Closest resource is a tree and hit result is a tree
		if (closestResource->IsA(ATree::StaticClass()) && hitResult.GetActor()->IsA(ATree::StaticClass()))
		{
			sameResourceTypeInSphere.Add(hitResult);
		}

		// Closest resource is a stone and hit result is a stone
		if (closestResource->IsA(AStone::StaticClass()) && hitResult.GetActor()->IsA(AStone::StaticClass()))
		{
			sameResourceTypeInSphere.Add(hitResult);
		}
	}
	
	return sameResourceTypeInSphere;
}

void AAI_ProjectCharacter::SummonNPC(const FInputActionValue& Value)
{
	const FVector start = this->GetActorLocation();
	const FCollisionShape sphereCollision = FCollisionShape::MakeSphere(this->SummonDistance);
	TArray<FHitResult> hitResults;

	DrawDebugSphere(GetWorld(), start, sphereCollision.GetSphereRadius(), 10, FColor::Cyan, false, 1.0f);
	GetWorld()->SweepMultiByChannel(hitResults, start, start, FQuat::Identity, ECC_NPC, sphereCollision);
	
	//for (FHitResult HitResult : hitResults)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Hit: %s"), *(HitResult.GetActor()->GetName())));
	//}
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Hit: %d"), hitResults.Num()));
	//return;
}
