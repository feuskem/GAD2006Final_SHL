// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"
#include "Engine/Texture2D.h"
#include "Components/SphereComponent.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ItemName = "Unnamed Item";
	ItemDescription = "No description available.";
	ItemIcon = nullptr;

	// Root component olarak bir SphereComponent ekleyebilirsiniz
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;

}

void ABaseItem::OnInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Interacting with item: %s"), *ItemName);
}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

