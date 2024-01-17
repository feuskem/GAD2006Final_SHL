// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "FinishJob.generated.h"

/**
 * 
 */
UCLASS()
class AFinishJob : public AInteractable
{
	GENERATED_BODY()
	

public:
	virtual void Interact_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsTargetQuotaReached;

	

	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
	void OnInteract();
};
