// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraGameplayAbility.h"

#include "Player/AuraPlayerController.h"


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
	AAuraPlayerController* AuraPlayerController=Cast<AAuraPlayerController>(GetWorld()->GetFirstPlayerController());
	AuraPlayerController->Ability2Level[this]++;
}

void UAuraGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	AAuraPlayerController* AuraPlayerController=Cast<AAuraPlayerController>(GetWorld()->GetFirstPlayerController());
	TPair<UAuraGameplayAbility*,int32>AbilityLevel(Spec.Ability,1);
	AuraPlayerController->Ability2Level.Add(AbilityLevel);
}
