// Fill out your copyright notice in the Description page of Project Settings.


#include "Dooor.h"




ADooor::ADooor() 
{

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrame->SetupAttachment(RootComponent);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(DoorFrame);
	bIsDoorOpen = false;

}

void ADooor::Interact_Implementation()
{

	if (!bIsDoorOpen)
	{
		// If the door is closed, open it
		Door->SetRelativeRotation(FRotator(0.f, 90.f, 0.f)); // Adjust the rotation values as needed
	}
	else
	{
		// If the door is open, close it
		Door->SetRelativeRotation(FRotator(0.f, 0.f, 0.f)); // Adjust the rotation values as needed
	}

	bIsDoorOpen = !bIsDoorOpen;
	

}





	




