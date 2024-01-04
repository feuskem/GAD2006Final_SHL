// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ladder.generated.h"

UCLASS()
class ALadder : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALadder();
	UPROPERTY(EditAnywhere, Category = "Mesh")
	class UStaticMeshComponent* LadderMesh;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	class UBoxComponent* Box;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	class UBoxComponent* Box2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Overlap(UPrimitiveComponent* Overlap, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	FTimerHandle DelayHandle;
		
	UFUNCTION()
	void SetActorLocationUp();
	float FloatDelay = 0.2f;

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};