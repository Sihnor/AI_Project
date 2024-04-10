// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackBoard/Task/NPC/Project_BTTask_StartWork.h"

EBTNodeResult::Type UProject_BTTask_StartWork::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
