// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI_Package.h"
#include "AIController.h"
#include "Project_NPC_AIController.generated.h"

/**
 * 
 */
UCLASS()
class AI_PROJECT_API AProject_NPC_AIController : public AAIController, public IAI_Package
{
	GENERATED_BODY()

public:
	// Implement IAI_Package interface
	UFUNCTION()
	virtual void Collect() override;
	UFUNCTION()
	virtual void Summon(TArray<FHitResult> npcs) override;
	UFUNCTION()
	virtual void Command(TArray<FHitResult> resources) override;

	// Get ListAi
	UFUNCTION(BlueprintCallable, Category = "AI")
	UProject_DataAsset_ListAI* GetListAI() const { return this->ListAI.Get(); }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|GameEvents")
	TObjectPtr<class UProject_DA_GameEvent> CommandEvent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|GameEvents")
	TObjectPtr<class UProject_DA_GameEvent> SummonEvent;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	TObjectPtr<class UProject_DataAsset_ListAI> ListAI;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|GameEvents")
	TObjectPtr<class UProject_DA_GameEvent_Vector> FollowEvent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBlackboardComponent> BlackboardComponent;

public:
	AProject_NPC_AIController(FObjectInitializer const& ObjectInitializer);

	virtual void BeginPlay() override;
	
	virtual void OnPossess(APawn* InPawn) override;
	
};
