// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "DrawDebugHelpers.h"



// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetMesh(), "Camera");

	

}



// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();


	CurrentInteractable = nullptr;

	Inventory.SetNum(4);
	
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckForInteractables();

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ABaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ABaseCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABaseCharacter::JumpPressed);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABaseCharacter::JumpReleased);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ABaseCharacter::Interact);
	PlayerInputComponent->BindAction("DropItem", IE_Pressed, this, &ABaseCharacter::DropItem);

	PlayerInputComponent->BindAction("AA", IE_Pressed, this, &ABaseCharacter::SwitchSlot1);
	PlayerInputComponent->BindAction("AB", IE_Pressed, this, &ABaseCharacter::SwitchSlot2);
	PlayerInputComponent->BindAction("AC", IE_Pressed, this, &ABaseCharacter::SwitchSlot3);
	PlayerInputComponent->BindAction("AD", IE_Pressed, this, &ABaseCharacter::SwitchSlot4);
	
}

void ABaseCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ABaseCharacter::JumpPressed()
{
	bPressedJump = true;
}

void ABaseCharacter::JumpReleased()
{
	bPressedJump = false;
}

void ABaseCharacter::LookUp(float Value)
{
	
}

void ABaseCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}



bool ABaseCharacter::AddItemToInventory(APickup* Item)
{
	
	if (Item != NULL)
	{
		const int32 AvailableSlot = Inventory.Find(nullptr);

		if (AvailableSlot != INDEX_NONE)
		{
			Inventory[AvailableSlot] = Item;
			return true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("You cannot carry more items!"));
			return false;
		}

	}
	else return false;

}

UTexture2D* ABaseCharacter::GetThumbnailAtInventorySlot(int32 Slot)
{
	if (Inventory[Slot] != NULL)
	{
		return Inventory[Slot]->PickupTexture;
	}
	else return nullptr;
}

FString ABaseCharacter::GivenItemNameAtInventorySlot(int32 Slot)
{
	if (Inventory[Slot] != NULL)
	{
		return Inventory[Slot]->ItemName;
	}

	return FString("None");
}

void ABaseCharacter::UseItemAtInventorySlot(int32 Slot)
{
	if (Inventory[Slot] != NULL)
	{
		Inventory[Slot]->Use_Implementation();
		Inventory[Slot] = NULL;
	}

}

void ABaseCharacter::DropItem()
{
	if (Inventory.IsValidIndex(CurrentSlotIndex) && Inventory[CurrentSlotIndex] != nullptr)
	{
		
		FActorSpawnParameters SpawnParams;
		FTransform SpawnTransform = GetActorTransform();
		APickup* DroppedItem = GetWorld()->SpawnActor<APickup>(Inventory[CurrentSlotIndex]->GetClass(), SpawnTransform, SpawnParams);

		if (DroppedItem)
		{
			DroppedItem->ItemName = Inventory[CurrentSlotIndex]->ItemName;
			DroppedItem->PickupTexture = Inventory[CurrentSlotIndex]->PickupTexture;
			DroppedItem->Value = Inventory[CurrentSlotIndex]->Value;
		}

		
		Inventory[CurrentSlotIndex] = nullptr;

		
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Dropped %s from Slot %d"), *DroppedItem->ItemName, CurrentSlotIndex));
	}
}



void ABaseCharacter::Interact()
{
	if (CurrentInteractable !=nullptr)
	{
		CurrentInteractable->Interact_Implementation();

		
	}

	
}

void ABaseCharacter::CheckForInteractables()
{
	FVector StartLocation = CameraComponent->GetComponentLocation();
	FVector ForwardVector = CameraComponent->GetForwardVector();
	FVector EndLocation = StartLocation + (ForwardVector * 200);

	FHitResult HitResult;

	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_WorldDynamic, CQP);

	AInteractable* PotentialInteractable = Cast<AInteractable>(HitResult.GetActor());

	if (PotentialInteractable == NULL)
	{
		UIText = FString("");
		CurrentInteractable = nullptr;
		return;
	}
	else
	{
		CurrentInteractable = PotentialInteractable;
		UIText = PotentialInteractable->UIText;
	}

	/*ADoorActor* Door = Cast<ADoorActor>(HitResult.GetActor());
	if (Door) {
		Door->OnInteract();
	}*/
}

void ABaseCharacter::SwitchInventorySlot(int32 NewSlotIndex)
{

	if (NewSlotIndex >= 0 && NewSlotIndex < Inventory.Num())
	{
		
		CurrentSlotIndex = NewSlotIndex;

		

		
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Active Slot: %d"), CurrentSlotIndex));
	}
}



void ABaseCharacter::SwitchSlot1()
{
	SwitchInventorySlot(0);
	
}

void ABaseCharacter::SwitchSlot2()
{
	SwitchInventorySlot(1);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Slot2!"));
	
}

void ABaseCharacter::SwitchSlot3()
{
	SwitchInventorySlot(2);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Slot3!"));
	
}

void ABaseCharacter::SwitchSlot4()
{
	SwitchInventorySlot(3);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Slot4!"));
	
}



