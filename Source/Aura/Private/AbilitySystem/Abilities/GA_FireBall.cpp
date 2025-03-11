// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GA_FireBall.h"

#include "AbilitySystemComponent.h"
#include "Actor/ProjectileFireBall.h"


void UGA_FireBall::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if(!CommitAbility(Handle,ActorInfo,ActivationInfo))
	{
		CancelAbility(Handle,ActorInfo,ActivationInfo,true);
		return;
	}

	CommitAbilityCooldown(Handle,ActorInfo,ActivationInfo,false);
	
	SpawnFireball();

	EndAbility(Handle,ActorInfo,ActivationInfo,true,false);
}



void UGA_FireBall::SpawnFireball() const
{
	if (const AActor* Avatar = GetAvatarActorFromActorInfo())
	{
		const FVector SpawnLocation = Avatar->GetActorLocation() + Avatar->GetActorForwardVector() * 100.0f;
		const FRotator SpawnRotation = Avatar->GetActorRotation();
        
		AProjectileFireBall* Fireball = GetWorld()->SpawnActor<AProjectileFireBall>(FireBallClass, SpawnLocation, SpawnRotation);
	}
}
