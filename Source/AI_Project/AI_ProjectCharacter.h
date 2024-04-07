// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AI_ProjectCharacter.generated.h"

class USphereComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AAI_ProjectCharacter : public ACharacter
{
	GENERATED_BODY()

#pragma region PropertiesComponents
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NPCs|GameEvents", meta = (AllowPrivateAccess = "true"))
	USphereComponent* FollowPointSphere;

#pragma endregion

#pragma region PropertiesInput
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPCs", meta = (AllowPrivateAccess = "true"))
	UInputAction* CommandNPCAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPCs", meta = (AllowPrivateAccess = "true"))
	UInputAction* SummonNPCAction;

#pragma endregion

#pragma region PropertiesGameEvents
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NPCs|GameEvents", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UProject_DA_GameEvent> CommandEvent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NPCs|GameEvents", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UProject_DA_GameEvent> SummonEvent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NPCs|GameEvents", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UProject_DA_GameEvent_Vector> FollowEvent;

#pragma endregion
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCs", meta = (AllowPrivateAccess = "true"))
	int ResourceSphereRadius = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCs", meta = (AllowPrivateAccess = "true"))
	float SummonSphereRadius = 1000.0f;
	
	FVector FollowPointLocation;
	
public:
	AAI_ProjectCharacter();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void CommandNPC(const FInputActionValue& Value);

	void SummonNPC(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	bool GetAllResourcesInBox(TArray<FHitResult>& result) const;
	bool GetClosestResource(FHitResult& results) const;
	TArray<FHitResult> GetSameResourceTypeInSphere(FHitResult closestResource) const;

	void FollowPoint();
	void SetFollowPointLocation(const FVector& location);
	
	
};

