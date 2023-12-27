// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "Wheel.generated.h"

/**
 * 
 */
UCLASS()
class AWheel : public ABaseItem
{
	GENERATED_BODY()

public:

	AWheel();

	virtual void OnInteract() override;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Wheel")
	int32 CreditsValue;
	
	

};
