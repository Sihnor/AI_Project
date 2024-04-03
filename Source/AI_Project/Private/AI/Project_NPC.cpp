// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Project/Public/AI/Project_NPC.h"

#include "AI/Project_DataAsset_ListAI.h"
#include "AI/Project_DA_GameEvent.h"
#include "Components/SphereComponent.h"


// Sets default values
AProject_NPC::AProject_NPC()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	this->SphereComponent->InitSphereRadius(32.0f);
	this->SphereComponent->SetRelativeScale3D(FVector(5.5f, 5.5f, 5.5f));
	this->SphereComponent->SetCollisionProfileName(TEXT("Trigger"));
	this->SphereComponent->SetupAttachment(RootComponent);
	this->SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProject_NPC::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AProject_NPC::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProject_NPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AProject_NPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AProject_NPC::Collect()
{
	IAI_Package::Collect();

	if (this->ListAI) this->ListAI->RegisterAI(this);
}

void AProject_NPC::Summon(TArray<FHitResult> npcs)
{
	if (this->NPCState == ENPCState::Masterless) return;

	for (FHitResult result : npcs)
	{
		if (result.GetActor() != this) continue;
		
		this->NPCState = ENPCState::Following;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Summoned"));
	}
}

void AProject_NPC::Command(TArray<FHitResult> resources)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Commanded"));
}

void AProject_NPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(OtherActor->GetOwner()))
	{
		if (this->IsCollected() != ENPCState::Masterless) return;
		
		if (this->CommandEvent) this->CommandEvent.Get()->OnEvent.AddUniqueDynamic(this, &AProject_NPC::Command);
		if (this->SummonEvent) this->SummonEvent.Get()->OnEvent.AddUniqueDynamic(this, &AProject_NPC::Summon);

		this->Collect();
	}
}
