// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/Data/SkillInfoData.h"
#include "AuraGameplayAbility.generated.h"

class UAuraGameplayAbility;
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

UCLASS(Blueprintable, BlueprintType)
class AURA_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	UMaterialInstance* IconMaterial;

	UFUNCTION(BlueprintCallable, Category = "AbilityInfo")
	FGameplayAbilityInfo GetAbilityInfo(int level);

	UPROPERTY(VisibleAnywhere)
	int32 CurrentSkillLevel = 1;

	UPROPERTY(EditDefaultsOnly,Category="Skill UI")
	TSoftObjectPtr<USkillInfoData> SkillInfoData;

	UFUNCTION(BlueprintCallable)
	USkillInfoData* GetSkillInfoData()const{return SkillInfoData.LoadSynchronous();}

	UFUNCTION(BlueprintCallable)
	virtual void UpgradeAbility();

protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
};
