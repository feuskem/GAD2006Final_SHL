// Fill out your copyright notice in the Description page of Project Settings.


#include "Wheel.h"

AWheel::AWheel()
{
	CreditsValue = 45;
}

void AWheel::OnInteract()
{

	Super::OnInteract();

	
	UE_LOG(LogTemp, Warning, TEXT("Interacting with Wheel! CreditsValue: %d credits"), CreditsValue);
}
