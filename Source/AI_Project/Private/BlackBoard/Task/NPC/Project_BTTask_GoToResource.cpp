// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackBoard/Task/NPC/Project_BTTask_GoToResource.h"

#include "Navigation/PathFollowingComponent.h"
#include "AI/Project_NPC_AIController.h"

EBTNodeResult::Type UProject_BTTask_GoToResource::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bNotifyTick = true;
	
	AProject_NPC_AIController* AIController = Cast<AProject_NPC_AIController>(OwnerComp.GetAIOwner());
	
	FVector ResourcePosition;
	AIController->CanGetNextResourcePosition(ResourcePosition);
	
	AIController->MoveToLocation(ResourcePosition);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Moving to resource"));

	return EBTNodeResult::InProgress;
}

void UProject_BTTask_GoToResource::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (OwnerComp.GetAIOwner()->GetMoveStatus() == EPathFollowingStatus::Type::Idle)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
