// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Project_BTTask_FinishCommand.generated.h"

/**
 * 
 */
UCLASS()
class AI_PROJECT_API UBTTask_FinishCommand : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
    EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
