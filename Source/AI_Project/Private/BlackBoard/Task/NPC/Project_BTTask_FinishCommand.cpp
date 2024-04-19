// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackBoard/Task/NPC/Project_BTTask_FinishCommand.h"

#include "AI/Project_NPC_AIController.h"

EBTNodeResult::Type UBTTask_FinishCommand::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    bNotifyTick = true;
    Cast<AProject_NPC_AIController>(OwnerComp.GetAIOwner())->Collect();

    return EBTNodeResult::Failed;
}

