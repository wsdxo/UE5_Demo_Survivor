// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "Character/AuraCharacter.h"
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
	GetAbilityLevel();
}

void UAuraGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	
	if (ActorInfo && ActorInfo->AvatarActor.IsValid())
	{
		if (AAuraCharacter* AuraCharacter = Cast<AAuraCharacter>(ActorInfo->AvatarActor.Get()))
		{
			AuraCharacter->OwnedAbilities.Add(this);
		}
	}
}

