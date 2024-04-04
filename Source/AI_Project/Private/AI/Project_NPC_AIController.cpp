// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Project_NPC_AIController.h"

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
}


void AProject_NPC_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(this->Blackboard.Get()) && IsValid(this->BehaviorTree.Get()))
	{
		this->Blackboard->InitializeBlackboard(*this->BehaviorTree->BlackboardAsset);
	}
}
