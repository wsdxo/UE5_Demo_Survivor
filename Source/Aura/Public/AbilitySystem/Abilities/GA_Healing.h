// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraGameplayAbility.h"
#include "GA_Healing.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UGA_Healing : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(EditDefaultsOnly,Category="Gameplay Effect")
	TSubclassOf<UGameplayEffect>HealingEffect;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;


private:
	void ApplyEffectToTarget(AActor* TargetActor,TSubclassOf<UGameplayEffect>GameplayEffectClass);
};
