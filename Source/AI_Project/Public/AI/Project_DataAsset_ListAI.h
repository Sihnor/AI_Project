// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Project_DataAsset_ListAI.generated.h"

class AProject_NPC;
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
	TArray<AProject_NPC*> ListOfAllNPCs;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TArray<AProject_NPC*> ListOfAllFollowingNPCs;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TArray<AProject_NPC*> ListOfAllCommandedNPCs;

	UFUNCTION(BlueprintCallable, Category = "AI")
	void RegisterAI(AProject_NPC* AI);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void AddFollowingAI(AProject_NPC* AI);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void AddCommandedAI(AProject_NPC* AI);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void RemoveAI(AProject_NPC* AI);
	
};
