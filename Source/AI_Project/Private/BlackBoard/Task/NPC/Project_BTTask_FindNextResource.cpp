// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackBoard/Task/NPC/Project_BTTask_FindNextResource.h"

#include "AI/Project_NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UProject_BTTask_FindNextResource::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bNotifyTick = true;

	AProject_NPC_AIController* const NPC_AIController = Cast<AProject_NPC_AIController>(OwnerComp.GetAIOwner());
	const bool IsThereANextResource = NPC_AIController->IsThereARemainingResource();

	if (!IsThereANextResource)
	{
		NPC_AIController->Collect_NPC_AI();
		return EBTNodeResult::Failed;
	}
	
	FVector ResourcePosition;
	NPC_AIController->GetNextResourcePosition(ResourcePosition);

	UBlackboardComponent* const Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	Blackboard->SetValueAsVector(TEXT("ResourcePosition"), ResourcePosition);

	return EBTNodeResult::Succeeded;
}

void UProject_BTTask_FindNextResource::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (Cast<AProject_NPC_AIController>(OwnerComp.GetAIOwner())->GetNPCState() != ENPCState::Commanded)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
}
