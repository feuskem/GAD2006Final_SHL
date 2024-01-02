// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "SHL_GameInstance.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FItemDataStruct : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    FString ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    FString ItemDescription;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    UTexture2D* ItemIcon;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    float Weight;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName ItemID;
};



UCLASS()
class USHL_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
    USHL_GameInstance();

    UFUNCTION(BlueprintPure, Category = "Item")
    FItemDataStruct GetItemData(FName ItemName);

private:
    // Veri tablosu referansý
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
    class UDataTable* ItemDataTable;

};

