// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "Chain.generated.h"

/**
 * 
 */
UCLASS()
class AChain : public ABaseItem
{
	GENERATED_BODY()
public:

	AChain();

	virtual void OnInteract() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Chain")
	int32 CreditsValue;

	
};
