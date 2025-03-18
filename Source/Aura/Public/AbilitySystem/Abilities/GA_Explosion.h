// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraGameplayAbility.h"
#include "GA_Explosion.generated.h"

class AProjectileExplosion;
/**
 * 
 */
UCLASS()
class AURA_API UGA_Explosion : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
public:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditDefaultsOnly,Category="Explosion")
	TSubclassOf<AProjectileExplosion>ExplosionClass;
private:
	void SpawnExplosion()const;
};
