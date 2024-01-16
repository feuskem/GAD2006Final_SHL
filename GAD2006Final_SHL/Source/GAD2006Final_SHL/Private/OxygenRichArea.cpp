// Fill out your copyright notice in the Description page of Project Settings.


#include "OxygenRichArea.h"
#include "BaseCharacter.h"

// Sets default values
AOxygenRichArea::AOxygenRichArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));  // Set the size of the box
    RootComponent = CollisionBox;

    // Bind functions for overlap events
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AOxygenRichArea::OnOverlapBegin);
    CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AOxygenRichArea::OnOverlapEnd);

}

// Called when the game starts or when spawned
void AOxygenRichArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOxygenRichArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOxygenRichArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ABaseCharacter* PlayerCharacter = Cast<ABaseCharacter>(OtherActor);
    if (PlayerCharacter)
    {
        // Start increasing oxygen when the overlap begins
        PlayerCharacter->GetWorldTimerManager().SetTimer(PlayerCharacter->OxygenRichAreaTimerHandle, PlayerCharacter, &ABaseCharacter::IncreaseOxygenFromArea, 1.0f, true);
    }

}

void AOxygenRichArea::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

    ABaseCharacter* PlayerCharacter = Cast<ABaseCharacter>(OtherActor);
    if (PlayerCharacter)
    {
        // Stop increasing oxygen when the overlap ends
        PlayerCharacter->GetWorldTimerManager().ClearTimer(PlayerCharacter->OxygenRichAreaTimerHandle);
    }

}

