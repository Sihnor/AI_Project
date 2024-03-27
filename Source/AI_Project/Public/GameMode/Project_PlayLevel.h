// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Project_PlayLevel.generated.h"

/**
 * 
 */
UCLASS()
class AI_PROJECT_API AProject_PlayLevel : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	TObjectPtr<class UProject_DataAsset_ListAI> ListAI;
};
