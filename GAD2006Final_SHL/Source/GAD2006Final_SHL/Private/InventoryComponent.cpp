// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent(): MaxSlots(4)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	InventorySlots.Init(nullptr, MaxSlots);

	// ...
}



void UInventoryComponent::DropItem(int32 SlotIndex)
{
    if (SlotIndex >= 0 && SlotIndex < MaxSlots)
    {
        
        if (InventorySlots[SlotIndex] == nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("DropItem called for an empty slot. Slot Index: %d"), SlotIndex);
            return;
        }

        
        int32 EmptySlotIndex = INDEX_NONE;
        for (int32 i = 0; i < MaxSlots; ++i)
        {
            if (!InventorySlots[i])
            {
                EmptySlotIndex = i;
                break;
            }
        }

        
        if (EmptySlotIndex != INDEX_NONE)
        {
            
            if (SlotIndex == 0)
            {
                DropItem(SlotIndex);
            }
            else
            {
               
                for (int32 i = 0; i < MaxSlots; ++i)
                {
                    if (!InventorySlots[i])
                    {
                        EmptySlotIndex = i;
                        break;
                    }
                }
            }

           
            InventorySlots[SlotIndex] = nullptr;
            UE_LOG(LogTemp, Warning, TEXT("DropItem called. Slot Index: %d"), SlotIndex);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid Slot Index! Slot Index: %d"), SlotIndex);
    }
}

int32 UInventoryComponent::FindOccupiedSlot()
{
    for (int32 i = 0; i < MaxSlots; ++i)
    {
        if (InventorySlots[i])
        {
          
            return i;
        }
    }

    
    return INDEX_NONE;
}







// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

