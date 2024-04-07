// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Project_DataAsset_ListAI.generated.h"

/**
 * 
 */
UCLASS()
class AI_PROJECT_API UProject_DataAsset_ListAI : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UProject_DataAsset_ListAI();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TArray<class AProject_NPC_AIController*> ListOfAllNPCs;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TArray<AProject_NPC_AIController*> ListOfAllFollowingNPCs;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TArray<AProject_NPC_AIController*> ListOfAllCommandedNPCs;
	

	UFUNCTION(BlueprintCallable, Category = "AI")
	void RegisterAI(AProject_NPC_AIController* AI);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void AddFollowingAI(AProject_NPC_AIController* AI);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void AddCommandedAI(AProject_NPC_AIController* AI);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void RemoveAI(AProject_NPC_AIController* AI);
	
};
