// Fill out your copyright notice in the Description page of Project Settings.


#include "Chain.h"

AChain::AChain()
{
	CreditsValue = 25;
}

void AChain::OnInteract()
{

	Super::OnInteract();


	UE_LOG(LogTemp, Warning, TEXT("Interacting with Chain! CreditsValue: %d credits"), CreditsValue)
}
