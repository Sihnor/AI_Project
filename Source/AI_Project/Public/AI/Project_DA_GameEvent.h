// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Project_DA_GameEvent.generated.h"

class AResource;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEvent, TArray<FHitResult>, npc);

UCLASS()
class AI_PROJECT_API UProject_DA_GameEvent : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Game Event")
	FOnEvent OnEvent;
	
};
