// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollectibleRes.h"
#include "Resource.h"
#include "Stone.generated.h"

UCLASS()
class AI_PROJECT_API AStone : public AResource, public ICollectibleRes
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStone();

public:
	void RegisterNPC();
	void UnregisterNPC();

	EResourceType GetResourceType();
	int32 GetRemainingPlaces();
};
