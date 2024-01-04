#include "BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Pickup.h"

APickup::APickup()
{

	InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh"));
	InteractableMesh->SetSimulatePhysics(true);

	ItemName = FString("Enter an item name");
	UIText = FString("Press E to pick up");
	Value = 0;
	Weight = 0;

}

void APickup::BeginPlay()
{
	UIText = FString::Printf(TEXT("% s press E to pick up"), *ItemName);
}

void APickup::Interact_Implementation()
{

	ABaseCharacter* Character = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (Character->AddItemToInventory(this))
	{

		OnPickedUp();

	}


}

void APickup::Use_Implementation()
{



}

void APickup::OnPickedUp()
{

	InteractableMesh->SetVisibility(false);
	InteractableMesh->SetSimulatePhysics(false);
	InteractableMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}