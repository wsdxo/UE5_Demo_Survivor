// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GA_Healing.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Character/AuraCharacter.h"


void UGA_Healing::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                  const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if(!CommitAbility(Handle,ActorInfo,ActivationInfo))
	{
		CancelAbility(Handle,ActorInfo,ActivationInfo,true);
		return;
	}
	CommitAbilityCooldown(Handle,ActorInfo,ActivationInfo,false);

	if(AAuraCharacter* AuraCharacter=Cast<AAuraCharacter>(ActorInfo->AvatarActor))
	{
		ApplyEffectToTarget(AuraCharacter,HealingEffect);
	}
	
	EndAbility(Handle,ActorInfo,ActivationInfo,true,false);
}

void UGA_Healing::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if(!TargetASC)return;
	FGameplayEffectContextHandle EffectContextHandle=TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle=TargetASC->MakeOutgoingSpec(GameplayEffectClass,GetAbilityLevel(),EffectContextHandle);

	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}


