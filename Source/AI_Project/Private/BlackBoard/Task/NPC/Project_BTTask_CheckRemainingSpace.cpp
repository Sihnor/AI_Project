// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackBoard/Task/NPC/Project_BTTask_CheckRemainingSpace.h"

#include "AI/Project_NPC_AIController.h"

EBTNodeResult::Type UProject_BTTask_CheckRemainingSpace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bNotifyTick = true;
	AProject_NPC_AIController* const Controller = Cast<AProject_NPC_AIController>(OwnerComp.GetAIOwner());
	
	if (Controller->RegisterResource()) return EBTNodeResult::Succeeded;
	if (!Controller->IsThereARemainingResource()) Cast<AProject_NPC_AIController>(OwnerComp.GetAIOwner())->Collect();

	return EBTNodeResult::Failed;
}

void UProject_BTTask_CheckRemainingSpace::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBTTask_BlackboardBase::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (Cast<AProject_NPC_AIController>(OwnerComp.GetAIOwner())->GetNPCState() != ENPCState::Commanded)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
}
