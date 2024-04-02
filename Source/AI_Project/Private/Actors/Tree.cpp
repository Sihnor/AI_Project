// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Project/Public/Actors/Tree.h"


// Sets default values
ATree::ATree()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->ResourceType = EResourceType::Tree;
	this->PlacesNPCsCanCollect = 4;
	this->RemainingPlacesNPCsCanCollect = 4;
}

void ATree::RegisterNPC()
{
	this->RemainingPlacesNPCsCanCollect--;
}

void ATree::UnregisterNPC()
{
	this->RemainingPlacesNPCsCanCollect++;
}

EResourceType ATree::GetResourceType()
{
	return this->ResourceType;
}

int32 ATree::GetRemainingPlaces()
{
	return this->RemainingPlacesNPCsCanCollect;
}

