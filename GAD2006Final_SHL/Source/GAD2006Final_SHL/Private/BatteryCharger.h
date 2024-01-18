// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "BatteryCharger.generated.h"

/**
 * 
 */
UCLASS()
class ABatteryCharger : public AInteractable
{
	GENERATED_BODY()
	
	ABatteryCharger();

	virtual void Interact_Implementation() override;


public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float Charger;

};
