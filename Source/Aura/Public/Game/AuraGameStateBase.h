// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AuraGameStateBase.generated.h"

class AEnemySpawner;
class AAuraEnemy;
/**
 * 
 */
UCLASS()
class AURA_API AAuraGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<AAuraEnemy*>ActiveEnemies;

	UPROPERTY()
	TArray<AEnemySpawner*>EnemySpawners;
	
	UFUNCTION()
	void AddEnemy(AAuraEnemy* Enemy);
    
	UFUNCTION()
	void RemoveEnemy(AAuraEnemy* Enemy);
};
