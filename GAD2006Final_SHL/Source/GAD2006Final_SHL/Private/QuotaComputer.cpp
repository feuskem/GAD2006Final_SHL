// Fill out your copyright notice in the Description page of Project Settings.


#include "QuotaComputer.h"
#include "BaseCharacter.h"
#include "Sound/SoundBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"


AQuotaComputer::AQuotaComputer() 
{
    static ConstructorHelpers::FObjectFinder<USoundBase> QuotaSoundAsset(TEXT("/Script/Engine.SoundWave'/Game/UI_Widget/quotacomputersfx.quotacomputersfx'"));

    QuotaSound = QuotaSoundAsset.Object;

}


void AQuotaComputer::Interact_Implementation()
{

    

    UE_LOG(LogTemp, Warning, TEXT("Quota deðeri: %d"),Quota);

   
    ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if (BaseCharacter)
    {
        
        if (BaseCharacter->Inventory.IsValidIndex(BaseCharacter->CurrentSlotIndex) &&
            BaseCharacter->Inventory[BaseCharacter->CurrentSlotIndex] != nullptr)
        {
            UGameplayStatics::PlaySound2D(this, QuotaSound);

            Quota += BaseCharacter->Inventory[BaseCharacter->CurrentSlotIndex]->Value;

            
            BaseCharacter->CurrentWeight -= BaseCharacter->Inventory[BaseCharacter->CurrentSlotIndex]->Weight;

            
            BaseCharacter->Inventory[BaseCharacter->CurrentSlotIndex] = nullptr;

            
        }
    }


}
