// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI_Package.h"
#include "GameFramework/Character.h"
#include "Project_NPC.generated.h"

class UBehaviorTree;

UCLASS()
class AI_PROJECT_API AProject_NPC : public ACharacter, public IAI_Package
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameEvents")
	TObjectPtr<class UProject_DA_GameEvent> CommandEvent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameEvents")
	TObjectPtr<class UProject_DA_GameEvent> SummonEvent;	

public:
	// Sets default values for this character's properties
	AProject_NPC();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTree;

	UFUNCTION(BlueprintCallable, Category = "AI", meta = (AllowPrivateAccess = "true"))
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// Implement IAI_Package interface
	UFUNCTION()
	virtual void Collect() override;
	UFUNCTION()
	virtual void Summon(TArray<FHitResult> npcs) override;
	UFUNCTION()
	virtual void Command(TArray<FHitResult> resources) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	TObjectPtr<class UProject_DataAsset_ListAI> ListAI;

	// Get ListAi
	UFUNCTION(BlueprintCallable, Category = "AI")
	UProject_DataAsset_ListAI* GetListAI() const { return this->ListAI.Get(); }

public:
	UFUNCTION(BlueprintCallable, Category = "AI")
	UBehaviorTree* GetBehaviorTree() const { return this->BehaviorTree; }
};
