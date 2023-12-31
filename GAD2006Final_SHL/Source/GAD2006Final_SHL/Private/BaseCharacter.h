// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Interactable.h"
#include "Pickup.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "BaseCharacter.generated.h"



UCLASS()
class ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void JumpPressed();
	void JumpReleased();
	void LookUp(float Value);
	void Turn(float Value);

private:
	UPROPERTY(EditAnywhere)
	FTimerHandle HealthDecreaseTimerHandle;

public:

	UPROPERTY(EditAnywhere)
	float TimeSinceLastHealthDecrease;



	UPROPERTY(EditAnywhere)
	bool Moveup;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComponent;

	


	float BaseTurnRate;
	float BaseLookUpRate;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WalkSpeed = 450.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RunSpeed = 750.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Stamina = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStamina = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinStamina = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StaminaDrainRate = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StaminaGainRate = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HoldingRunKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
	bool StaminaDrained;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GasMask;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Oxygen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString UIText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentWeight;


	//Character Creation

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Endurance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Capacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Points;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxOxygen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentOxygen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OxygenDecreaseRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeSinceLastOxygenDecrease;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool GasMaskOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthDecreaseRate;

	
	


	AInteractable* CurrentInteractable;

	UFUNCTION(BlueprintPure)
	bool AddItemToInventory(APickup* Item);

	
	void UpdateOxygen(float DeltaTime);


	void DecreaseOxygen();

	UFUNCTION(BlueprintPure)
	UTexture2D* GetThumbnailAtInventorySlot(int32 Slot);

	UFUNCTION(BlueprintPure)
	FString GivenItemNameAtInventorySlot(int32 Slot);

	UFUNCTION(BlueprintCallable)
	void UseItemAtInventorySlot(int32 Slot);

	UFUNCTION(BlueprintCallable)
	void DropItem();

	void RunPressed();
	void RunReleased();
	void UpdateMovementParams();
	void UseGasMask();
	void IsGasMaskOn();
	void DecreaseHealth();
	void UpdateHealth(float DeltaTime);
private:

	UPROPERTY(EditAnywhere)
	TArray<APickup*> Inventory;

	void Interact();

	void CheckForInteractables();

	int32 CurrentSlotIndex;

	void SwitchInventorySlot(int32 NewSlotIndex);

	void SwitchSlot1();
	void SwitchSlot2();
	void SwitchSlot3();
	void SwitchSlot4();

	void Use();
	
};
