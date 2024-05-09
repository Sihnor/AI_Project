// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCState.h"
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
protected:

	ENPCState NPCState = ENPCState::Masterless;
	

public:
	virtual void Collect_NPC_AI()
	{
		this->NPCState = ENPCState::Following;
	}

	UFUNCTION(Category = "AI")
	virtual void Summon_NPC_AI(TArray<FHitResult> targets) = 0;

	UFUNCTION(Category = "AI")
	virtual void Command_NPC_AI(TArray<FHitResult> resource) = 0;

	UFUNCTION(Category = "AI")
	virtual void StartFollowing_NPC_AI() = 0;

	ENPCState IsCollected() const { return this->NPCState; }
};
