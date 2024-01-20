// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Dooor.generated.h"

/**
 * 
 */
UCLASS()
class ADooor : public AInteractable
{
	GENERATED_BODY()

	ADooor();
	

public:
	virtual void Interact_Implementation() override;
	

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* DoorFrame;
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Door;
	

	bool bIsDoorOpen = true;


	
	

	

	

};
