// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraEnemy.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class AURA_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,Category="Spawn Settings")
	TSubclassOf<AAuraEnemy>EnemyClass;

	UPROPERTY(EditAnywhere,Category="Spawn Settigns")
	float SpwanInterval;
	
	UPROPERTY(EditAnywhere,Category="Spawn Settings")
	int32 MaxEnemyCount;

private:
	FTimerHandle SpawnTimerHandle;
	TArray<AAuraEnemy*>ActiveEnemies;

	UFUNCTION()
	void SpawnEnemy();

	UFUNCTION()
	void OnEnemyDestroyed(AActor* DestroyedActor);
};
