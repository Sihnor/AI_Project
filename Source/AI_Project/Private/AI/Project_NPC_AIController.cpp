// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Project_NPC_AIController.h"

#include "Actors/Resource.h"
#include "AI/Project_DataAsset_ListAI.h"
#include "AI/Project_DA_GameEvent.h"
#include "AI/Project_DA_GameEvent_Vector.h"
#include "AI/Project_NPC.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AProject_NPC_AIController::AProject_NPC_AIController(FObjectInitializer const& ObjectInitializer)
{
	this->BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	this->BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AProject_NPC_AIController::BeginPlay()
{
	Super::BeginPlay();

	if (this->BehaviorTree)
	{
		this->RunBehaviorTree(this->BehaviorTree);
		this->BehaviorTreeComponent->StartTree(*this->BehaviorTree);
	}

	this->NPCState = ENPCState::Masterless;
	if (BlackboardComponent) BlackboardComponent->SetValueAsEnum(TEXT("NPC_State"), static_cast<uint8>(this->NPCState));
}


void AProject_NPC_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(this->Blackboard.Get()) && IsValid(this->BehaviorTree.Get()))
	{
		this->Blackboard->InitializeBlackboard(*this->BehaviorTree->BlackboardAsset);
	}
}

void AProject_NPC_AIController::Collect()
{
	IAI_Package::Collect();
	
	if (this->CommandEvent) this->CommandEvent.Get()->OnEvent.AddUniqueDynamic(this, &AProject_NPC_AIController::Command);
	if (this->SummonEvent) this->SummonEvent.Get()->OnEvent.AddUniqueDynamic(this, &AProject_NPC_AIController::Summon);
	if (this->FollowEvent) this->FollowEvent.Get()->OnEvent.AddUniqueDynamic(this, &AProject_NPC_AIController::Follow);

	if (this->ListAI) this->ListAI->RegisterAI(this);
	
	if (BlackboardComponent) BlackboardComponent->SetValueAsEnum(TEXT("NPC_State"), static_cast<uint8>(this->NPCState));
}

void AProject_NPC_AIController::Summon(TArray<FHitResult> npcs)
{
	if (this->NPCState == ENPCState::Masterless) return;
	this->ResourceIndex = 0;

	for (FHitResult result : npcs)
	{
		if (result.GetActor()->GetInstigatorController() != this) continue;
		
		this->NPCState = ENPCState::Following;
		this->ListAI->AddFollowingAI(this);

		this->StopWork();

		if (BlackboardComponent) BlackboardComponent->SetValueAsEnum(TEXT("NPC_State"), static_cast<uint8>(this->NPCState));
	}
}

void AProject_NPC_AIController::Command(TArray<FHitResult> resources)
{
	if (this->NPCState != ENPCState::Following) return;

	this->ResourcesList.Empty();
	
	for (FHitResult Element : resources)
	{
		this->ResourcesList.Add(Cast<AResource>(Element.GetActor()));
	}

	this->NPCState = ENPCState::Commanded;
	this->ResourceIndex = 0;
	this->ListAI->AddCommandedAI(this);
	if (BlackboardComponent) BlackboardComponent->SetValueAsEnum(TEXT("NPC_State"), static_cast<uint8>(this->NPCState));
}

void AProject_NPC_AIController::Follow(FVector location)
{
	if (this->BlackboardComponent) BlackboardComponent->SetValueAsVector(TEXT("FollowPoint"), location);
}

bool AProject_NPC_AIController::RegisterResource()
{
	return this->ResourcesList[this->ResourceIndex - 1]->RegisterWorker();
}

bool AProject_NPC_AIController::CanGetNextResourcePosition(FVector& location)
{
	if (this->ResourceIndex > this->ResourcesList.Num() -1) return false;
	UE_LOG(LogTemp, Warning, TEXT("ResourceIndex: %d"), this->ResourcesList.Num());

	location = this->ResourcesList[this->ResourceIndex]->GetActorLocation();

	this->ResourceIndex++;
	
	return true;
}

void AProject_NPC_AIController::FaceResource()
{
	APawn* const ControlledPawn = GetPawn();

	if (!ControlledPawn) return;

	FVector Direction = this->ResourcesList[this->ResourceIndex - 1]->GetActorLocation() - ControlledPawn->GetActorLocation();
	Direction.Z = 0;

	FRotator const Rotator = FRotationMatrix::MakeFromX(Direction).Rotator();
	ControlledPawn->SetActorRotation(Rotator);
}
