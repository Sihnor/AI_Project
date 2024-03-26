// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Project/Public/AI/Project_NPC.h"


// Sets default values
AProject_NPC::AProject_NPC()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AProject_NPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProject_NPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AProject_NPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

