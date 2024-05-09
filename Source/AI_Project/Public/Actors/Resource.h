// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Resource.generated.h"


class AProject_NPC;

UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AI_PROJECT_API AResource : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Resource")
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category = "Resource")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Resource")
	int QuantityOfWorker = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Resource")
	int QuantityOfWorkerRemaining;

public:
	// Sets default values for this actor's properties
	AResource();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual bool RegisterWorker();
	virtual void UnregisterWorker();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|GameEvents")
	TObjectPtr<class UProject_DA_GameEvent_Zero> CollectResourceEvent;	

	virtual void CollectResource() PURE_VIRTUAL(); 
};
