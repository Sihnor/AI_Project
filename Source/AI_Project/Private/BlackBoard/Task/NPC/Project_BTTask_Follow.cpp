// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackBoard/Task/NPC/Project_BTTask_Follow.h"

#include "NavigationSystem.h"
#include "AI/Project_NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UProject_BTTask_Follow::UProject_BTTask_Follow(FObjectInitializer const& ObjectInitializer)
{
	this->NodeName = "Follow the player character";
}

EBTNodeResult::Type UProject_BTTask_Follow::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bNotifyTick = true;
	
	AProject_NPC_AIController* AIController = Cast<AProject_NPC_AIController>(OwnerComp.GetAIOwner());
	
	
	UBlackboardComponent* const Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	FVector FollowPoint = Blackboard->GetValueAsVector(TEXT("FollowPoint"));
	

	return EBTNodeResult::InProgress;
}

void UProject_BTTask_Follow::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	
	if (AProject_NPC_AIController* AIController = Cast<AProject_NPC_AIController>(OwnerComp.GetAIOwner()))
	{
		if (AIController->GetNPCState() == ENPCState::Commanded)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
	}

	UBlackboardComponent* const Blackboard = OwnerComp.GetBlackboardComponent();

	FVector FollowPoint = Blackboard->GetValueAsVector(TEXT("FollowPoint"));
	
	AProject_NPC_AIController* AIController = Cast<AProject_NPC_AIController>(OwnerComp.GetAIOwner());
	AIController->MoveToLocation(FollowPoint);
}
