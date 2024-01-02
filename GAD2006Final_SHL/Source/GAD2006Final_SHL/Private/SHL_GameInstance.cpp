// Fill out your copyright notice in the Description page of Project Settings.


#include "SHL_GameInstance.h"

USHL_GameInstance::USHL_GameInstance()
{
    static ConstructorHelpers::FObjectFinder<UDataTable> ItemDataTableObject(TEXT("/Script/Engine.DataTable'/Game/Blueprints/ItemDataTable.ItemDataTable'"));
    if (ItemDataTableObject.Succeeded())
    {
        ItemDataTable = ItemDataTableObject.Object;
    }
}

FItemDataStruct USHL_GameInstance::GetItemData(FName ItemName)
{
    FItemDataStruct* ItemData = ItemDataTable->FindRow<FItemDataStruct>(ItemName, FString(""));
    if (ItemData)
    {
        return *ItemData;
    }
    else
    {
        // Hata durumunda boþ bir FItemDataStruct döndürülebilir veya hata mesajý gösterilebilir.
        return FItemDataStruct();
    }
}
