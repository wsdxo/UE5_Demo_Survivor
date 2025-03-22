// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraGameplayAbility.h"
#include "GA_FightBack.generated.h"

class AEffectActor;
/**
 * 
 */
UCLASS()
class AURA_API UGA_FightBack : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly,Category="Projectile")
	TSubclassOf<AEffectActor>ProjectileClass;

	UPROPERTY(EditDefaultsOnly,Category="Projectile")
	int32 ProjectileNum=6;

	UPROPERTY(EditDefaultsOnly,Category="Projectile")
	float SpawnRadius=0.f;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	void SpawnProjectile()const;
	
};
