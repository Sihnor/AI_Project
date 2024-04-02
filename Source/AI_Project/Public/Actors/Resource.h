// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourceType.h"
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
	
public:
	// Sets default values for this actor's properties
	AResource();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
