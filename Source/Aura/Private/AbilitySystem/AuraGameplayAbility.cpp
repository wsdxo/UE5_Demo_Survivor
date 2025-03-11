// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraGameplayAbility.h"

FGameplayAbilityInfo::FGameplayAbilityInfo():
	CD(0),
	IconMaterial(nullptr),
	AbilityClass(nullptr)
{

}

FGameplayAbilityInfo::FGameplayAbilityInfo(float CD, UMaterialInstance* IconMaterial, TSubclassOf<UAuraGameplayAbility> AbilityClass):
	CD(CD),
	IconMaterial(IconMaterial),
	AbilityClass(AbilityClass)
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
