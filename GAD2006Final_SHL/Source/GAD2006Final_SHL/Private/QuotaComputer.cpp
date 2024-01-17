// Fill out your copyright notice in the Description page of Project Settings.


#include "QuotaComputer.h"
#include "BaseCharacter.h"


void AQuotaComputer::Interact_Implementation()
{

    // Super class'taki Interact_Implementation fonksiyonunu �a��r

    UE_LOG(LogTemp, Warning, TEXT("Quota de�eri: %d"),Quota);

   // E�er sahip oldu�umuz s�n�f ABaseCharacter ise devam et
    ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if (BaseCharacter)
    {
        // E�er oyuncunun envanterinde se�ili slot bo� de�ilse devam et
        if (BaseCharacter->Inventory.IsValidIndex(BaseCharacter->CurrentSlotIndex) &&
            BaseCharacter->Inventory[BaseCharacter->CurrentSlotIndex] != nullptr)
        {
            // Quota de�erini art�r
            Quota += BaseCharacter->Inventory[BaseCharacter->CurrentSlotIndex]->Value;

            // Oyuncunun toplam a��rl���ndan se�ili slotun a��rl���n� ��kar
            BaseCharacter->CurrentWeight -= BaseCharacter->Inventory[BaseCharacter->CurrentSlotIndex]->Weight;

            // Se�ili slotu temizle
            BaseCharacter->Inventory[BaseCharacter->CurrentSlotIndex] = nullptr;

            // Di�er i�lemleri buraya ekleyebilirsin
            // �rne�in, Quota'n�n belirli bir de�eri ge�ip ge�medi�ini kontrol edebilir ve
            // belirli bir de�eri ge�ti�inde �zel bir i�lem yapabilirsin.
        }
    }


}
