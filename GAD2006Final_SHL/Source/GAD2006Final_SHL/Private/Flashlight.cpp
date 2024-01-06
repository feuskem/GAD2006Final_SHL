// Fill out your copyright notice in the Description page of Project Settings.


#include "Flashlight.h"

AFlashlight::AFlashlight()
{
	LightIntensity = 1000.0f;
	bIsFlashlightOn = false;

	FlashlightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("FlashlightComponent"));
	FlashlightComponent->SetIntensity(LightIntensity);
	FlashlightComponent->SetLightColor(FLinearColor::White);
	FlashlightComponent->SetOuterConeAngle(30.0f);
	FlashlightComponent->SetAttenuationRadius(2000.0f);

	InteractableMesh->SetSimulatePhysics(false);

	
		// Attach FlashlightComponent to InteractableMesh
		FlashlightComponent->SetupAttachment(InteractableMesh);
}

void AFlashlight::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFlashlight::Interact_Implementation()
{
	Super::Interact_Implementation();
	ToggleFlashlight();
}

void AFlashlight::Use_Implementation()
{
	ToggleFlashlight();
}

void AFlashlight::ToggleFlashlight()
{
	bIsFlashlightOn = !bIsFlashlightOn;

	if (bIsFlashlightOn)
	{
		FlashlightComponent->SetVisibility(true);
		
	}
	else
	{
		FlashlightComponent->SetVisibility(false);
		
	}
}
