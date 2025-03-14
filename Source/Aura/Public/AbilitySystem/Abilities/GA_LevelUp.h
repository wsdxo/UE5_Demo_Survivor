// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraGameplayAbility.h"
#include "GA_LevelUp.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UGA_LevelUp : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_LevelUp();

	UFUNCTION(BlueprintNativeEvent)
	void ShowLevelUpUI();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override; 

protected:
	UPROPERTY(EditDefaultsOnly,Category="LevelUpUI")
	TSubclassOf<UUserWidget>LevelUpUIClass;

	TObjectPtr<UUserWidget>LevelUpUIInstance;
	
	
};
