// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Project_NPC_AIController.h"

#include "AI/Project_NPC.h"
#include "BehaviorTree/BehaviorTree.h"

AProject_NPC_AIController::AProject_NPC_AIController(FObjectInitializer const& ObjectInitializer)
{
}
 
void AProject_NPC_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (AProject_NPC* const npc = Cast<AProject_NPC>(InPawn))
	{
		if (UBehaviorTree* const behaviorTree = npc->GetBehaviorTree())
		{
			UBlackboardComponent* blackboardComponent = nullptr;
			UseBlackboard(behaviorTree->BlackboardAsset, blackboardComponent);
			Blackboard = blackboardComponent;
			RunBehaviorTree(behaviorTree);
		}
	}
}
