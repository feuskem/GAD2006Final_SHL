// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"
#include "BaseCharacter.h"
#include "InventoryComponent.h"
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

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	
	

}



// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	PlayerInputComponent->BindAction("DropItem", IE_Pressed, this, &ABaseCharacter::DropItemFromInventory);
}

void ABaseCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector
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



void ABaseCharacter::Interact()
{
	if (!CameraComponent)
	{
		// Kamera bileþeni yoksa çýkýþ yap
		return;
	}

	FVector StartLocation = CameraComponent->GetComponentLocation();
	FVector ForwardVector = CameraComponent->GetForwardVector();
	FVector EndLocation = StartLocation + (ForwardVector * 200); // Örnek: 200 birim ileriye doðru line trace
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;

	// Line trace yap
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams))
	{
		// Çizgiyi çiz
		DrawDebugLine(GetWorld(), StartLocation, HitResult.Location, FColor::Green, false, 2.0f, 0, 1.0f);

		ABaseItem* HitItem = Cast<ABaseItem>(HitResult.GetActor());
		if (HitItem)
		{
			
			int32 EmptySlotIndex = INDEX_NONE;
			for (int32 i = 0; i < InventoryComponent->MaxSlots; ++i)
			{
				if (!InventoryComponent->InventorySlots[i])
				{
					EmptySlotIndex = i;
					break;
				}
			}

			if (EmptySlotIndex != INDEX_NONE)
			{
				InventoryComponent->InventorySlots[EmptySlotIndex] = HitItem;
				
				HitItem->Destroy();
			}
		}
		else
		{
			
		}
	}
}

void ABaseCharacter::DropItemFromInventory()
{
	int32 OccupiedSlotIndex = InventoryComponent->FindOccupiedSlot();
	if (OccupiedSlotIndex != INDEX_NONE)
	{
		ABaseItem* ItemToDrop = InventoryComponent->InventorySlots[OccupiedSlotIndex];

		if (ItemToDrop)
		{
			FVector SpawnLocation = GetActorLocation() + (GetActorForwardVector() * 100); 
			FRotator SpawnRotation = FRotator::ZeroRotator;
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;

			
			ABaseItem* SpawnedItem = GetWorld()->SpawnActor<ABaseItem>(ItemToDrop->GetClass(), SpawnLocation, SpawnRotation, SpawnParams);

			
			InventoryComponent->InventorySlots[OccupiedSlotIndex] = nullptr;

			UE_LOG(LogTemp, Warning, TEXT("DropItemFromInventory called. Occupied Slot Index: %d"), OccupiedSlotIndex);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DropItemFromInventory called, but no occupied slot found."));
	}
}


