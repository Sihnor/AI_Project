// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Project_InGameUI.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class AI_PROJECT_API UProject_InGameUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|GameEvents")
	TObjectPtr<class UProject_DA_GameEvent_Zero> CollectResourceEvent;	
	
	UPROPERTY(meta = (BindWidget))
	UImage* StoneImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StoneCounterTextBlock;

	UPROPERTY(meta = (BindWidget))
	UImage* WoodImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* WoodCounterTextBlock;
};
