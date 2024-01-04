// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "SHL_GameInstance.generated.h"

/**
 * 
 */




UCLASS()
class USHL_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
    USHL_GameInstance();
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SavedStrength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SavedEndurance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SavedCapacity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SavedHealth;



};

