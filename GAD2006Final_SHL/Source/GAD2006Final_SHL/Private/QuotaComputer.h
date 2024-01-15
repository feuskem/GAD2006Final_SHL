// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "QuotaComputer.generated.h"

/**
 * 
 */
UCLASS()
class AQuotaComputer : public AInteractable
{
	GENERATED_BODY()
	
public:

	virtual void Interact_Implementation() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Quota;

};
