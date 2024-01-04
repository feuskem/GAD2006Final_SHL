// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class ADoor : public AInteractable
{
	GENERATED_BODY()

	ADoor();

protected:
    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* DoorMesh;

    bool bIsDoorOpen;

public:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;


    virtual void Interact_Implementation() override;
	
};
