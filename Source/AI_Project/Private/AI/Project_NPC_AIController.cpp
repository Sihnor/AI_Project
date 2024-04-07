// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Project_NPC_AIController.h"

#include "AI/Project_DataAsset_ListAI.h"
#include "AI/Project_DA_GameEvent.h"
#include "AI/Project_NPC.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

void AProject_NPC_AIController::Collect()
{
	IAI_Package::Collect();
	
	if (this->CommandEvent) this->CommandEvent.Get()->OnEvent.AddUniqueDynamic(this, &AProject_NPC_AIController::Command);
	if (this->SummonEvent) this->SummonEvent.Get()->OnEvent.AddUniqueDynamic(this, &AProject_NPC_AIController::Summon);

	if (this->ListAI) this->ListAI->RegisterAI(this);
}

void AProject_NPC_AIController::Summon(TArray<FHitResult> npcs)
{
	if (this->NPCState == ENPCState::Masterless) return;

	for (FHitResult result : npcs)
	{
		if (result.GetActor()->GetInstigatorController() != this) continue;
		
		this->NPCState = ENPCState::Following;
		this->ListAI->AddFollowingAI(this);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Summoned"));
	}
}

void AProject_NPC_AIController::Command(TArray<FHitResult> resources)
{
	if (this->NPCState != ENPCState::Following) return;

	this->NPCState = ENPCState::Commanded;
	this->ListAI->AddCommandedAI(this);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Commanded"));
}

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
}


void AProject_NPC_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(this->Blackboard.Get()) && IsValid(this->BehaviorTree.Get()))
	{
		this->Blackboard->InitializeBlackboard(*this->BehaviorTree->BlackboardAsset);
	}
}
