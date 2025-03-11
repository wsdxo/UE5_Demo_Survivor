// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraGameplayAbility.h"
#include "GA_FireBall.generated.h"

/**
 * 
 */

class AProjectileFireBall;

UCLASS()
class AURA_API UGA_FireBall : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Fireball")
	TSubclassOf<AProjectileFireBall> FireBallClass;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
private:

	void SpawnFireball() const;
};
