// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "Flashlight.generated.h"

/**
 * 
 */
UCLASS()
class AFlashlight : public APickup
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool TurnOn;
	
};
