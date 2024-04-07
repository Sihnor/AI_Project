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


	return EBTNodeResult::Failed;
	UBlackboardComponent* const blackboard = OwnerComp.GetBlackboardComponent();

	//if (!blackboard) return EBTNodeResult::Failed;

	//blackboard->SetValueAsVector(TEXT("FollowPoint"), FVector(0.f, 0.f, 0.f));
	

	
	
	if (AProject_NPC_AIController* const controller = Cast<AProject_NPC_AIController>(OwnerComp.GetAIOwner()))
	{
		if (APawn* const npc = controller->GetPawn())
		{

			if (UNavigationSystemV1* const nacSys = UNavigationSystemV1::GetCurrent((GetWorld())))
			{
				//OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), )
			}
		}
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
