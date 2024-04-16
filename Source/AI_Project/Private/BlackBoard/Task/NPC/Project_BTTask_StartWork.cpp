// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackBoard/Task/NPC/Project_BTTask_StartWork.h"

#include "AI/Project_NPC_AIController.h"

EBTNodeResult::Type UProject_BTTask_StartWork::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bNotifyTick = true;

	AProject_NPC_AIController* Controller = Cast<AProject_NPC_AIController>(OwnerComp.GetAIOwner());

	Controller->StartWork();
	Controller->FaceResource();
	
	
	return EBTNodeResult::InProgress;
}

void UProject_BTTask_StartWork::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AProject_NPC_AIController* Controller = Cast<AProject_NPC_AIController>(OwnerComp.GetAIOwner());

	if (Controller)
	{
		if (Controller->GetNPCState() != ENPCState::Commanded)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
	}
}
