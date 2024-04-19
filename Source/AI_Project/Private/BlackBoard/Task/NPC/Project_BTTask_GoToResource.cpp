// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackBoard/Task/NPC/Project_BTTask_GoToResource.h"

#include "Navigation/PathFollowingComponent.h"
#include "AI/Project_NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UProject_BTTask_GoToResource::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bNotifyTick = true;
	
	AProject_NPC_AIController* AIController = Cast<AProject_NPC_AIController>(OwnerComp.GetAIOwner());
	UBlackboardComponent* const Blackboard = OwnerComp.GetBlackboardComponent();

	const FVector ResourcePosition = Blackboard->GetValueAsVector(TEXT("ResourcePosition"));
	
	AIController->MoveToLocation(ResourcePosition, 1);

	return EBTNodeResult::InProgress;
}

void UProject_BTTask_GoToResource::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (Cast<AProject_NPC_AIController>(OwnerComp.GetAIOwner())->GetNPCState() != ENPCState::Commanded)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	if (OwnerComp.GetAIOwner()->GetMoveStatus() == EPathFollowingStatus::Type::Idle)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
