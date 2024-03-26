// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Project/Public/Actors/Stone.h"


// Sets default values
AStone::AStone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AStone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

