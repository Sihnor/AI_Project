// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Project_BTTask_Follow.generated.h"

/**
 * 
 */
UCLASS()
class AI_PROJECT_API UProject_BTTask_Follow : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UProject_BTTask_Follow(FObjectInitializer const& ObjectInitializer);	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
