// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Character/AuraCharacter.h"
#include "Net/UnrealNetwork.h"


UAuraAttributeSet::UAuraAttributeSet()
{
	InitAttributes();
}

void UAuraAttributeSet::InitAttributes()
{
	InitMaxHealth(100);
	InitHealth(100);
	InitXP(1);
	InitLevel(1);
}

void UAuraAttributeSet::InitAttributes(float InitialMaxHealth, float InitialHealth)
{
	InitMaxHealth(InitialMaxHealth);
	InitHealth(InitialHealth);
	InitXP(1);
	InitLevel(1);
}

void UAuraAttributeSet::SetAttributes(float InitialMaxHealth, float InitialHealth)
{
	SetMaxHealth(InitialMaxHealth);
	SetHealth(InitialHealth);
}


void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if(Attribute==GetHealthAttribute())
	{
		NewValue=FMath::Clamp(NewValue,0,GetMaxHealth());

		if(NewValue<=GetMaxHealth()*0.4f&&GetHealth()>=GetMaxHealth()*0.4f)
		{
			if(UAbilitySystemComponent* AbilitySystemComponent=GetOwningAbilitySystemComponent())
			{
				FGameplayTagContainer HealingTag;
				HealingTag.AddTag(FGameplayTag::RequestGameplayTag("Ability.Passive.Healing"));
				AbilitySystemComponent->TryActivateAbilitiesByTag(HealingTag);
			}
		}

		if(NewValue<=0&&GetHealth()>0)
		{
			if(UAbilitySystemComponent* AbilitySystemComponent=GetOwningAbilitySystemComponent())
			{
				FGameplayTagContainer DeathTag;
				DeathTag.AddTag(FGameplayTag::RequestGameplayTag("Ability.Death"));
				AbilitySystemComponent->TryActivateAbilitiesByTag(DeathTag);
			}
		}

		if(NewValue<GetHealth())
		{
			if(UAbilitySystemComponent* AbilitySystemComponent=GetOwningAbilitySystemComponent())
			{
				FGameplayTagContainer FightBackTag;
				FightBackTag.AddTag(FGameplayTag::RequestGameplayTag("Ability.Passive.FightBack"));
				AbilitySystemComponent->TryActivateAbilitiesByTag(FightBackTag);
			}
		}
	}
	if(Attribute==GetXPAttribute())
	{
		int32 NewLevel=LevelUpInfo->FindLevelForXP(NewValue);

		if(NewLevel>GetLevel())
		{
			GetOwningAbilitySystemComponent()->ApplyModToAttribute(
				GetLevelAttribute(),
				EGameplayModOp::Override,
				NewLevel
				);
		}
	}
	if(Attribute==GetLevelAttribute())
	{
		if(UAbilitySystemComponent* AbilitySystemComponent=GetOwningAbilitySystemComponent())
		{
			FGameplayTagContainer LevelUpTag;
			LevelUpTag.AddTag(FGameplayTag::RequestGameplayTag("Ability.LevelUp"));
			AbilitySystemComponent->TryActivateAbilitiesByTag(LevelUpTag);
		}
	}
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Health,COND_None,REPNOTIFY_Always);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxHealth,OldValue);
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Health,OldValue);
}

void UAuraAttributeSet::OnRep_XP(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,XP,OldValue);
}

void UAuraAttributeSet::OnRep_Level(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Level,OldValue);
}

float UAuraAttributeSet::GetCharacterLevel()
{
	return GetLevel();
}
