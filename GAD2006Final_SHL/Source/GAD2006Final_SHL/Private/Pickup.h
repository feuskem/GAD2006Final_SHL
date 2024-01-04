// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Pickup.generated.h"

class ABaseCharacter;
/**
 * 
 */
UCLASS()
class APickup : public AInteractable
{
	GENERATED_BODY()
	
public:

	APickup();

	virtual void BeginPlay() override;
	
	virtual void Interact_Implementation() override;

	UFUNCTION(BlueprintNativeEvent)
	void Use();
	virtual void Use_Implementation();

	UPROPERTY(EditAnywhere)
	FString ItemName;

	UPROPERTY(EditAnywhere)
	UTexture2D* PickupTexture;

	UPROPERTY(EditAnywhere)
	int32 Value;

	UPROPERTY(EditAnywhere)
	int32 Weight;

	UFUNCTION(BlueprintCallable)
	void OnPickedUp();
	
};
