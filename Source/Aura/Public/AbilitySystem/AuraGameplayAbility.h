// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FGameplayAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AbilityInfo")
	float CD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	UMaterialInstance* IconMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	
	TSubclassOf<UAuraGameplayAbility> AbilityClass;

	FGameplayAbilityInfo();
	FGameplayAbilityInfo(float CD,UMaterialInstance* IconMaterial,TSubclassOf<UAuraGameplayAbility> AbilityClass);
};

UCLASS()
class AURA_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	UMaterialInstance* IconMaterial;

	UFUNCTION(BlueprintCallable, Category = "AbilityInfo")
	FGameplayAbilityInfo GetAbilityInfo(int level);
	
	
};
