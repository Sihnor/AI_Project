// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Project_NPC_AIController.h"

#include "Actors/Resource.h"
#include "AI/Project_DataAsset_ListAI.h"
#include "AI/Project_DA_GameEvent_FHitResults.h"
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

void AProject_NPC_AIController::Collect_NPC_AI()
{
	IAI_Package::Collect_NPC_AI();
	
	if (this->CommandEvent) this->CommandEvent.Get()->OnEvent.AddUniqueDynamic(this, &AProject_NPC_AIController::Command_NPC_AI);
	if (this->SummonEvent) this->SummonEvent.Get()->OnEvent.AddUniqueDynamic(this, &AProject_NPC_AIController::Summon_NPC_AI);
	if (this->FollowEvent) this->FollowEvent.Get()->OnEvent.AddUniqueDynamic(this, &AProject_NPC_AIController::Follow);

	if (this->ListAI) this->ListAI->RegisterAI(this);
	
	if (BlackboardComponent) BlackboardComponent->SetValueAsEnum(TEXT("NPC_State"), static_cast<uint8>(this->NPCState));
}

void AProject_NPC_AIController::Summon_NPC_AI(TArray<FHitResult> npcs)
{
	if (this->NPCState == ENPCState::Masterless) return;
	

	for (FHitResult result : npcs)
	{
		if (result.GetActor()->GetInstigatorController() != this) continue;

		StartFollowing_NPC_AI();
		this->ElapsedTime = 0.0f;
	}
}

void AProject_NPC_AIController::Command_NPC_AI(TArray<FHitResult> resources)
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

void AProject_NPC_AIController::StartFollowing_NPC_AI()
{
	this->UnRegisterResource();
	this->StopWork();
	this->ResourcesList.Empty();

	this->ResourceIndex = 0;
	this->NPCState = ENPCState::Following;
	this->ListAI->AddFollowingAI(this);

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

void AProject_NPC_AIController::UnRegisterResource()
{
	if (this->ResourcesList.Num() == 0) return;
	
	this->ResourcesList[this->ResourceIndex - 1]->UnregisterWorker();
}

bool AProject_NPC_AIController::IsThereARemainingResource() const
{
	return (this->ResourceIndex < this->ResourcesList.Num());
}

void AProject_NPC_AIController::GetNextResourcePosition(FVector& location)
{
	location = this->ResourcesList[this->ResourceIndex]->GetActorLocation();

	this->ResourceIndex++;
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

void AProject_NPC_AIController::WorkOnResource(float DeltaSeconds)
{
	this->ElapsedTime += DeltaSeconds;

	if (this->ElapsedTime >= 5.0f)
	{
		this->ElapsedTime = 0.0f;
		this->ResourcesList[this->ResourceIndex - 1]->CollectResource();
	}
}