// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResourceType.h"
#include "Engine/DataAsset.h"
#include "Project_DA_GameEvent_Zero.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEventZero, EResourceType, ResourceType);

UCLASS()
class AI_PROJECT_API UProject_DA_GameEvent_Zero : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Game Event")
	FOnEventZero OnEvent;
};
