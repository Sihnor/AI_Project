// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Project/Public/Actors/Stone.h"

#include "AI/Project_DA_GameEvent_Zero.h"


// Sets default values
AStone::AStone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->ResourceType = EResourceType::Stone;
	this->PlacesNPCsCanCollect = 8;
	this->RemainingPlacesNPCsCanCollect = 8;
}

void AStone::RegisterNPC()
{
	this->RemainingPlacesNPCsCanCollect--;
}

void AStone::UnregisterNPC()
{
	this->RemainingPlacesNPCsCanCollect++;
}

EResourceType AStone::GetResourceType()
{
	return this->ResourceType;
}

int32 AStone::GetRemainingPlaces()
{
	return this->RemainingPlacesNPCsCanCollect;
}

void AStone::CollectResource()
{
	this->CollectResourceEvent->OnEvent.Broadcast(this->ResourceType);
}
