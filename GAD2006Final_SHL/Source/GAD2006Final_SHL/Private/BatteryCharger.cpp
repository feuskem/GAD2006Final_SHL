// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryCharger.h"
#include "BaseCharacter.h"


ABatteryCharger::ABatteryCharger()
{
	Charger = 3;

}

void ABatteryCharger::Interact_Implementation()
{
	if (Charger > 0)
	{
		Charger -= 1;

		ABaseCharacter* PlayerCharacter = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (PlayerCharacter && PlayerCharacter->FlashlightBattery<=75)
		{
			
			PlayerCharacter->FlashlightBattery += 25;
		}
	}

}
