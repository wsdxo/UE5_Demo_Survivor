// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraGameplayAbility.h"


FGameplayAbilityInfo::FGameplayAbilityInfo()
{
	
}

FGameplayAbilityInfo::FGameplayAbilityInfo(float CD, UMaterialInstance* IconMaterial,
                                           TSubclassOf<UAuraGameplayAbility> AbilityClass)
{
	
}

FGameplayAbilityInfo UAuraGameplayAbility::GetAbilityInfo(int level)
{
	UGameplayEffect* CDEffect=GetCooldownGameplayEffect();
	float CD=0;

	if(CDEffect)
	{
		CDEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(level,CD);

		return FGameplayAbilityInfo(CD,IconMaterial,GetClass());
	}
	return FGameplayAbilityInfo();
}

void UAuraGameplayAbility::UpgradeAbility()
{
	CurrentSkillLevel++;
	
}
