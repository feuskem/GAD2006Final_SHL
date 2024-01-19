// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "DrawDebugHelpers.h"
#include "Gun.h"
#include "Sound/SoundBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetMesh(), "Camera");
	GetCharacterMovement()->MaxWalkSpeed = 450.0f;
	CurrentWeight = 0;
	GasMask = 1;
	FlashlightBattery = 100;
	MaxBattery = 100;
	Strength = 0;
	Endurance = 0;
	Capacity = 0;
	CurrentHealth = 3;
	MaxHealth = 5;
	BatteryDecreaseRate = 20;

	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/UI_Widget/pickup.pickup"));

	PickupSound = SoundAsset.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> DropItemSoundAsset(TEXT("/Game/UI_Widget/dropitemsfx.dropitemsfx"));

	DropSound = DropItemSoundAsset.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> FlashlightSoundAsset(TEXT("/Script/Engine.SoundWave'/Game/UI_Widget/Flashlight.Flashlight'"));

	FlashlightSound = FlashlightSoundAsset.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> ChangeFilterSoundAsset(TEXT("/Script/Engine.SoundWave'/Game/UI_Widget/UseFilter.UseFilter'"));

	ChangeFilterSound = ChangeFilterSoundAsset.Object;

	Points = 5;

	MaxOxygen = 100.0f;
	CurrentOxygen = MaxOxygen;
	HealthDecreaseRate = 1.0f;
	OxygenDecreaseRate = 10.0f; 
	TimeSinceLastOxygenDecrease = 0.0f;
	

}



// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();


	CurrentInteractable = nullptr;

	Inventory.SetNum(4);

	RunReleased();
	Stamina = MaxStamina;
	HoldingRunKey = false;
	StaminaDrained = false;

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{

	
	Super::Tick(DeltaTime);

	UpdateOxygen(DeltaTime);
	UpdateHealth(DeltaTime);
	UpdateBattery(DeltaTime);

	FString MoveUpStatus = Moveup ? FString(TEXT("Move Up")) : FString(TEXT("Not Move Up"));
	

	CheckForInteractables();
	if (CurrentWeight < 20)
	{
		
			StaminaDrainRate = 20.0f - 2*Capacity;
			StaminaGainRate = 15.0f +2*Capacity;	
		
	}
	else if (CurrentWeight >= 20 && CurrentWeight <40 )
	{
		StaminaDrainRate = 40.0f - 2 * Capacity;
		StaminaGainRate = 12.0f + 2 * Capacity;
	}
	else if (CurrentWeight >= 40)
	{
		StaminaDrainRate = 55.0f - 2 * Capacity;
		StaminaGainRate = 10.0f + 2 * Capacity;

	}


	if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking) {
		if (StaminaDrained)
		{
			Stamina = FMath::Min(MaxStamina, StaminaGainRate * DeltaTime + Stamina);

			if (MaxStamina == Stamina)
			{
				StaminaDrained = false;
				UpdateMovementParams();
			}
		}
		else
		{
			if (HoldingRunKey)
			{
				if (!GetCharacterMovement()->Velocity.IsNearlyZero(0.01f))
				{


					Stamina = FMath::Max(Stamina - StaminaDrainRate * DeltaTime, 0.0f);

					if (Stamina == 0.0f)
					{
						StaminaDrained = true;
						UpdateMovementParams();
					}
				}
				else {
					Stamina = FMath::Min(MaxStamina, Stamina + StaminaGainRate * DeltaTime);

					if (MaxStamina == Stamina)
					{
						StaminaDrained = false;
						UpdateMovementParams();
					}

				}
			}
			else
			{
				Stamina = FMath::Min(MaxStamina, Stamina + StaminaGainRate * DeltaTime);

				if (MaxStamina == Stamina)
				{
					StaminaDrained = false;
					UpdateMovementParams();
				}
			}
		}
	}




	

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
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &ABaseCharacter::Shoot);
    PlayerInputComponent->BindAction("ToggleFlashlight", IE_Pressed, this, &ABaseCharacter::ToggleFlashlight);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ABaseCharacter::Interact);
	PlayerInputComponent->BindAction("DropItem", IE_Pressed, this, &ABaseCharacter::DropItem);
	PlayerInputComponent->BindAction("Use", IE_Pressed, this, &ABaseCharacter::Use);
	PlayerInputComponent->BindAction("GasMask", IE_Pressed, this, &ABaseCharacter::IsGasMaskOn);
	PlayerInputComponent->BindAction("Filter", IE_Pressed, this, &ABaseCharacter::UseGasMask);

	PlayerInputComponent->BindAction("AA", IE_Pressed, this, &ABaseCharacter::SwitchSlot1);
	PlayerInputComponent->BindAction("AB", IE_Pressed, this, &ABaseCharacter::SwitchSlot2);
	PlayerInputComponent->BindAction("AC", IE_Pressed, this, &ABaseCharacter::SwitchSlot3);
	PlayerInputComponent->BindAction("AD", IE_Pressed, this, &ABaseCharacter::SwitchSlot4);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ABaseCharacter::RunPressed);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ABaseCharacter::RunReleased);

	
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

void ABaseCharacter::Shoot()
{
	Gun->PullTrigger();
}




void ABaseCharacter::DecreaseBattery()

{
	FlashlightBattery = FMath::Max(FlashlightBattery - BatteryDecreaseRate, 0.0f);
}




bool ABaseCharacter::AddItemToInventory(APickup* Item)
{
	
	if (Item != NULL)
	{
		const int32 AvailableSlot = Inventory.Find(nullptr);

		if (AvailableSlot != INDEX_NONE)
		{
			

			UGameplayStatics::PlaySound2D(this, PickupSound);

			CurrentWeight += Item->Weight;

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

void ABaseCharacter::UpdateOxygen(float DeltaTime)
{

	if (!GasMaskOn) {
		TimeSinceLastOxygenDecrease += DeltaTime;

		if (TimeSinceLastOxygenDecrease >= 6.0f)
		{
			DecreaseOxygen();
			TimeSinceLastOxygenDecrease = 0.0f;
		}

	}

	
}

void ABaseCharacter::IncreaseOxygenFromArea()
{

	const float OxygenIncreaseAmount = 5.0f;

	
	CurrentOxygen = FMath::Min(CurrentOxygen + OxygenIncreaseAmount, MaxOxygen);

}

void ABaseCharacter::DecreaseOxygen()
{
	CurrentOxygen = FMath::Max(CurrentOxygen - OxygenDecreaseRate, 0.0f);

}

void ABaseCharacter::UpdateBattery(float DeltaTime)
{

	if (!FlashlightOn) {
		TimeSinceLastBatteryDecrease += DeltaTime;

		if (TimeSinceLastBatteryDecrease >= 2.0f)
		{
			DecreaseBattery();
			TimeSinceLastBatteryDecrease = 0.0f;
		}

	}

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
		
	}

}

void ABaseCharacter::DropItem()
{
	if (Inventory.IsValidIndex(CurrentSlotIndex) && Inventory[CurrentSlotIndex] != nullptr)
	{
		int32 DroppedItemWeight = Inventory[CurrentSlotIndex]->Weight;

		UGameplayStatics::PlaySound2D(this, DropSound);

		
		FVector ForwardVector = GetActorForwardVector();

		
		FVector SpawnLocation = GetActorLocation() + ForwardVector *100;

		FActorSpawnParameters SpawnParams;
		FTransform SpawnTransform = FTransform(ForwardVector.Rotation(), SpawnLocation);

		APickup* DroppedItem = GetWorld()->SpawnActor<APickup>(Inventory[CurrentSlotIndex]->GetClass(), SpawnTransform, SpawnParams);

		if (DroppedItem)
		{
			DroppedItem->ItemName = Inventory[CurrentSlotIndex]->ItemName;
			DroppedItem->PickupTexture = Inventory[CurrentSlotIndex]->PickupTexture;
			DroppedItem->Value = Inventory[CurrentSlotIndex]->Value;
			DroppedItem->Weight = Inventory[CurrentSlotIndex]->Weight;
		}
		CurrentWeight -= DroppedItemWeight;

		Inventory[CurrentSlotIndex] = nullptr;

		
	}
}

void ABaseCharacter::RunPressed()
{

	HoldingRunKey = true;
	UpdateMovementParams();
}

void ABaseCharacter::RunReleased()
{

	HoldingRunKey = false;
	UpdateMovementParams();

}

void ABaseCharacter::UpdateMovementParams()
{

	if (!StaminaDrained && HoldingRunKey)
	{

		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}

	else
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}




void ABaseCharacter::UseGasMask()
{

	if (GasMask > 0 && CurrentOxygen <70)
	{
      GasMask -= 1;

	  UGameplayStatics::PlaySound2D(this, ChangeFilterSound);
	
	  CurrentOxygen += 30;

	}
	

}

void ABaseCharacter::IsGasMaskOn()
{
	GasMaskOn = !GasMaskOn;


}

void ABaseCharacter::DecreaseHealth()
{

	CurrentHealth = FMath::Max(CurrentHealth - HealthDecreaseRate, 0.0f);
}

void ABaseCharacter::UpdateHealth(float DeltaTime)
{

	if (CurrentOxygen == 0.0f || GasMaskOn)
	{
		TimeSinceLastHealthDecrease += DeltaTime;
		
		if (TimeSinceLastHealthDecrease >= 10.0f)
		{
			DecreaseHealth();
			TimeSinceLastHealthDecrease = 0.0f;
		}
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

		

		
	}
}



void ABaseCharacter::SwitchSlot1()
{
	SwitchInventorySlot(0);
	
}

void ABaseCharacter::SwitchSlot2()
{
	SwitchInventorySlot(1);
	
	
}

void ABaseCharacter::SwitchSlot3()
{
	SwitchInventorySlot(2);
	
	
}

void ABaseCharacter::SwitchSlot4()
{
	SwitchInventorySlot(3);
	
	
}

void ABaseCharacter::Use()
{
	if (CurrentInteractable != nullptr)
	{
		UseItemAtInventorySlot(CurrentSlotIndex);


	}

}

void ABaseCharacter::ToggleFlashlight()
{
	FlashlightOn = !FlashlightOn;

	UGameplayStatics::PlaySound2D(this, FlashlightSound);


}



