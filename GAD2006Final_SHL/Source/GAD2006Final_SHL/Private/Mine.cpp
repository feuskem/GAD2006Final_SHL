// Fill out your copyright notice in the Description page of Project Settings.


#include "Mine.h"
#include "Components/SphereComponent.h"
#include "TimerManager.h"
#include "BaseCharacter.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"


// Sets default values
AMine::AMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MineMesh"));
	RootComponent = MineMesh;
	ProxMineSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("ProxMineSphere"));
	ProxMineSphereComp->SetupAttachment(MineMesh);
	ProxMineSphereComp->OnComponentBeginOverlap.AddDynamic(this, &AMine::OnOverlapBegin);
	ProxMineSphereComp->OnComponentEndOverlap.AddDynamic(this, &AMine::OnOverlapEnd);

}

// Called when the game starts or when spawned
void AMine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMine::Explode()
{
	if (ABaseCharacter* Player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		Player->CurrentHealth -= 2;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), MineSoundCue, this->GetActorLocation());
		Destroy();
	}
}

void AMine::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GetWorld()->GetTimerManager().SetTimer(MineTimerHandle, this, &AMine::Explode, MineDelay, false);
	UE_LOG(LogTemp, Warning, TEXT("Collision occurred between %s and %s"), *GetName(), *OtherActor->GetName());
}

void AMine::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GetWorld()->GetTimerManager().ClearTimer(MineTimerHandle);
}



