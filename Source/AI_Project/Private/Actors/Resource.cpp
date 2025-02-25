// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Project/Public/Actors/Resource.h"


// Sets default values
AResource::AResource()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = this->Root;

	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	this->Mesh->SetupAttachment(this->Root);
}

// Called when the game starts or when spawned
void AResource::BeginPlay()
{
	Super::BeginPlay();

	this->QuantityOfWorkerRemaining = this->QuantityOfWorker;
}

// Called every frame
void AResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AResource::RegisterWorker()
{
	if (this->QuantityOfWorkerRemaining > 0)
	{
		this->QuantityOfWorkerRemaining--;
		return true;
	}

	return false;
}

void AResource::UnregisterWorker()
{
	this->QuantityOfWorkerRemaining++;

	if(this->QuantityOfWorkerRemaining >= this->QuantityOfWorker)
	{
		this->QuantityOfWorkerRemaining = this->QuantityOfWorker;
	}
}
