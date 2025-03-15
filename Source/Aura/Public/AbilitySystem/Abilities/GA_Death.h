// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraGameplayAbility.h"
#include "GA_Death.generated.h"

class AAuraCharacter;
/**
 * 
 */
UCLASS()
class AURA_API UGA_Death : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
	
public:

	UGA_Death();

	UFUNCTION(BlueprintNativeEvent)
	void ShowDeathUI();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	void AwardXPToPlayer(AAuraCharacter* TargetCharacter, int32 XPAward);

protected:
	UPROPERTY(EditDefaultsOnly,Category="DeathUI")
	TSubclassOf<UUserWidget>DeathUIClass;

	UPROPERTY()
	TObjectPtr<UUserWidget>DeathUIInstance;
	
};
