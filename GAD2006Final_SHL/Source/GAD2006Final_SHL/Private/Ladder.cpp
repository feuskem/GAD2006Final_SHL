// Fill out your copyright notice in the Description page of Project Settings.


#include "Ladder.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BaseCharacter.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ALadder::ALadder()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LadderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LadderMesh"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(LadderMesh);
	Box->OnComponentBeginOverlap.AddDynamic(this, &ALadder::Overlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ALadder::OnOverlapEnd);
	
}

// Called when the game starts or when spawned
void ALadder::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALadder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALadder::Overlap(UPrimitiveComponent* Overlap, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor))
	{
		Player->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		Player->Moveup = true;
	}
}

void ALadder::SetActorLocationUp()
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

void ALadder::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor))
	{

		Player->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		Player->Moveup = false;
	}
}


