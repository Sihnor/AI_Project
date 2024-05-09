// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI_Package.h"
#include "AIController.h"
#include "Project_NPC_AIController.generated.h"

class UProject_DataAsset_ListAI;
class AResource;
/**
 * 
 */
UCLASS()
class AI_PROJECT_API AProject_NPC_AIController : public AAIController, public IAI_Package
{
	GENERATED_BODY()

public:
	AProject_NPC_AIController(FObjectInitializer const& ObjectInitializer);

public:
	// Implement IAI_Package interface
	UFUNCTION()
	virtual void Collect_NPC_AI() override;
	UFUNCTION()
	virtual void Summon_NPC_AI(TArray<FHitResult> npcs) override;
	UFUNCTION()
	virtual void Command_NPC_AI(TArray<FHitResult> resources) override;
	UFUNCTION()
	virtual void StartFollowing_NPC_AI() override;

	UFUNCTION()
	void Follow(FVector location);
	
	// Get ListAi
	UFUNCTION(BlueprintCallable, Category = "AI")
	UProject_DataAsset_ListAI* GetListAI() const { return this->ListAI.Get(); }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|GameEvents")
	TObjectPtr<class UProject_DA_GameEvent_FHitResults> CommandEvent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|GameEvents")
	TObjectPtr<class UProject_DA_GameEvent_FHitResults> SummonEvent;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	TObjectPtr<class UProject_DataAsset_ListAI> ListAI;

	UPROPERTY()
	TArray<AResource*> ResourcesList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|GameEvents")
	TObjectPtr<class UProject_DA_GameEvent_Vector> FollowEvent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBlackboardComponent> BlackboardComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	bool bIsWorking = false;

public:
	virtual void BeginPlay() override;
	
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(BlueprintCallable, Category = "AI")
	ENPCState GetNPCState() const { return this->NPCState; }

	bool RegisterResource();
	void UnRegisterResource();
	bool IsThereARemainingResource() const;
	void GetNextResourcePosition(FVector& location);

	void StartWork() { this->bIsWorking = true; }
	void StopWork() { this->bIsWorking = false; }
	UFUNCTION(BlueprintCallable, Category = "AI")
	bool GetIsWorking() const { return this->bIsWorking; }

	void FaceResource();

	float ElapsedTime = 0.0f;
	void WorkOnResource(float DeltaSeconds);
	

private:
	int ResourceIndex = 0;
	
};
