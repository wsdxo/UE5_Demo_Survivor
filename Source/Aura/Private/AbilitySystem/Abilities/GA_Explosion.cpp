// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GA_Explosion.h"

#include "Actor/ProjectileExplosion.h"


void UGA_Explosion::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if(!CommitAbility(Handle,ActorInfo,ActivationInfo))
	{
		CancelAbility(Handle,ActorInfo,ActivationInfo,true);
		return;
	}

	CommitAbilityCooldown(Handle,ActorInfo,ActivationInfo,false);

	SpawnExplosion();

	EndAbility(Handle,ActorInfo,ActivationInfo,true,false);
}

void UGA_Explosion::SpawnExplosion() const
{
	if (const AActor* Avatar = GetAvatarActorFromActorInfo())
	{
		const FVector SpawnLocation = Avatar->GetActorLocation();

		AProjectileExplosion* Explosion=GetWorld()->SpawnActor<AProjectileExplosion>(ExplosionClass,SpawnLocation,FRotator::ZeroRotator);

		if(IsValid(Explosion))
		{
			Explosion->SetLevel(CurrentSkillLevel);
		}
	}
}
