// Fill out your copyright notice in the Description page of Project Settings.


#include "QuotaComputer.h"
#include "BaseCharacter.h"


void AQuotaComputer::Interact_Implementation()
{

    // Super class'taki Interact_Implementation fonksiyonunu çaðýr

    UE_LOG(LogTemp, Warning, TEXT("Quota deðeri: %d"),Quota);

   // Eðer sahip olduðumuz sýnýf ABaseCharacter ise devam et
    ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if (BaseCharacter)
    {
        // Eðer oyuncunun envanterinde seçili slot boþ deðilse devam et
        if (BaseCharacter->Inventory.IsValidIndex(BaseCharacter->CurrentSlotIndex) &&
            BaseCharacter->Inventory[BaseCharacter->CurrentSlotIndex] != nullptr)
        {
            // Quota deðerini artýr
            Quota += BaseCharacter->Inventory[BaseCharacter->CurrentSlotIndex]->Value;

            // Oyuncunun toplam aðýrlýðýndan seçili slotun aðýrlýðýný çýkar
            BaseCharacter->CurrentWeight -= BaseCharacter->Inventory[BaseCharacter->CurrentSlotIndex]->Weight;

            // Seçili slotu temizle
            BaseCharacter->Inventory[BaseCharacter->CurrentSlotIndex] = nullptr;

            // Diðer iþlemleri buraya ekleyebilirsin
            // Örneðin, Quota'nýn belirli bir deðeri geçip geçmediðini kontrol edebilir ve
            // belirli bir deðeri geçtiðinde özel bir iþlem yapabilirsin.
        }
    }


}
