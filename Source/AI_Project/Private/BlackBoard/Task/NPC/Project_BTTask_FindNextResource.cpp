// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackBoard/Task/NPC/Project_BTTask_FindNextResource.h"

#include "AI/Project_NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UProject_BTTask_FindNextResource::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FVector ResourcePosition;

	const bool IsThereANextResource = Cast<AProject_NPC_AIController>(OwnerComp.GetAIOwner())->CanGetNextResourcePosition(ResourcePosition);

	if (!IsThereANextResource) return EBTNodeResult::Failed;

	UBlackboardComponent* const Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	Blackboard->SetValueAsVector(TEXT("ResourcePosition"), ResourcePosition);

	return EBTNodeResult::Succeeded;
}
