// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Project_DataAsset_ListAI.h"

UProject_DataAsset_ListAI::UProject_DataAsset_ListAI()
{
}

void UProject_DataAsset_ListAI::RegisterAI(AProject_NPC* AI)
{
	if (this->ListOfAllNPCs.Contains(AI)) return;

	this->ListOfAllNPCs.Add(AI);
	this->AddFollowingAI(AI);
}

void UProject_DataAsset_ListAI::AddFollowingAI(AProject_NPC* AI)
{
	// Is this AI already in the list of following NPCs?
	if (this->ListOfAllFollowingNPCs.Contains(AI)) return;

	// If this AI is in the list of commanded NPCs, remove it from that list and add it to the list of following NPCs.
	if (this->ListOfAllCommandedNPCs.Contains(AI)) this->ListOfAllCommandedNPCs.Remove(AI);
	this->ListOfAllFollowingNPCs.Add(AI);
}

void UProject_DataAsset_ListAI::AddCommandedAI(AProject_NPC* AI)
{
	// Is this AI already in the list of commanded NPCs?
	if (this->ListOfAllCommandedNPCs.Contains(AI)) return;

	// If this AI is in the list of following NPCs, remove it from that list and add it to the list of commanded NPCs.
	if (this->ListOfAllFollowingNPCs.Contains(AI)) this->ListOfAllFollowingNPCs.Remove(AI);
	this->ListOfAllCommandedNPCs.Add(AI);
}

void UProject_DataAsset_ListAI::RemoveAI(AProject_NPC* AI)
{
	if (!this->ListOfAllNPCs.Contains(AI)) return;

	this->ListOfAllNPCs.Remove(AI);
}
