// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraEnemy.h"
#include "AuraRangedEnemy.generated.h"

class AEffectActor;
/**
 * 
 */
UCLASS()
class AURA_API AAuraRangedEnemy : public AAuraEnemy
{
	GENERATED_BODY()
	
	
public:
	AAuraRangedEnemy();
protected:

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(EditDefaultsOnly, Category="Ranged Attack")
	float AttackRange = 800.0f;

	UPROPERTY(EditDefaultsOnly, Category="Ranged Attack")
	float AttackInterval = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category="Ranged Attack")
	TSubclassOf<AEffectActor> ProjectileClass;
private:
	FTimerHandle AttackTimerHandle;
	bool bIsInAttackRange=false;

	void CheckDistanceToPlayer();
	
	void StartAttack();
	
	void StopAttack();
	
	void ShootProjectile();
	
};
