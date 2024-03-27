// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Project_DataAsset_ListAI.h"

UProject_DataAsset_ListAI::UProject_DataAsset_ListAI()
{
}

void UProject_DataAsset_ListAI::AddAI(AProject_NPC* AI)
{
	if (this->ListAI.Contains(AI)) return;

	this->ListAI.Add(AI);
}

void UProject_DataAsset_ListAI::RemoveAI(AProject_NPC* AI)
{
	if (!this->ListAI.Contains(AI)) return;

	this->ListAI.Remove(AI);
}
