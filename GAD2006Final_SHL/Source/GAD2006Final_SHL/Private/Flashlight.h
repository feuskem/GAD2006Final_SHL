// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "Components/SpotLightComponent.h"
#include "Flashlight.generated.h"

/**
 * 
 */
UCLASS()
class AFlashlight : public APickup
{
	GENERATED_BODY()

public:
	
public:

	AFlashlight();

	virtual void BeginPlay() override;

	virtual void Interact_Implementation() override;

	
	virtual void Use_Implementation() override;

	UFUNCTION(BlueprintCallable)
	void ToggleFlashlight();

	UPROPERTY(EditAnywhere)
	float LightIntensity;

	UPROPERTY(EditAnywhere)
	bool bIsFlashlightOn;

	UPROPERTY(EditAnywhere)
	class USpotLightComponent* FlashlightComponent;
	
};
