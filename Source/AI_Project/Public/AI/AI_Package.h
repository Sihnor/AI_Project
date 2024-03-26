// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AI_Package.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAI_Package : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AI_PROJECT_API IAI_Package
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	bool bIsCollected = false;

	
	void Collect();

	void Summon();

	void Command();
};
