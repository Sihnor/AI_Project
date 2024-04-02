// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Project_NPC_AIController.generated.h"

/**
 * 
 */
UCLASS()
class AI_PROJECT_API AProject_NPC_AIController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	TObjectPtr<class UProject_DataAsset_ListAI> ListAI;

public:
	AProject_NPC_AIController(FObjectInitializer const& ObjectInitializer);

	virtual void OnPossess(APawn* InPawn) override;
	
};
