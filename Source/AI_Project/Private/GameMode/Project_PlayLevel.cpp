// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/Project_PlayLevel.h"

#include "AI/Project_DataAsset_ListAI.h"

void AProject_PlayLevel::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (this->ListAI) this->ListAI->ListAI.Empty();
}
