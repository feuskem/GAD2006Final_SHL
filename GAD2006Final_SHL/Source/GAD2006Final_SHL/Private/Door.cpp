// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/StaticMeshComponent.h"

ADoor::ADoor()
{
	

PrimaryActorTick.bCanEverTick = true;

// Create the mesh component
DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
RootComponent = DoorMesh;

// Set default values
bIsDoorOpen = false;

}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

	


void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::Interact_Implementation()
{
    if (!bIsDoorOpen)
    {
        // If the door is closed, open it
        DoorMesh->SetRelativeRotation(FRotator(0.f, 90.f, 0.f)); // Adjust the rotation values as needed
    }
    else
    {
        // If the door is open, close it
        DoorMesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f)); // Adjust the rotation values as needed
    }

    bIsDoorOpen = !bIsDoorOpen;

}

