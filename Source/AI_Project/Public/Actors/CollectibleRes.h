// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CollectibleRes.generated.h"

enum class EResourceType : uint8;
// This class does not need to be modified.
UINTERFACE()
class UCollectibleRes : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AI_PROJECT_API ICollectibleRes
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
	EResourceType ResourceType;
	int32 PlacesNPCsCanCollect;
	int32 RemainingPlacesNPCsCanCollect;

public:
	void RegisterNPC();
	void UnregisterNPC();

	EResourceType GetResourceType() {return ResourceType;};
	int32 GetRemainingPlaces();
	
};
