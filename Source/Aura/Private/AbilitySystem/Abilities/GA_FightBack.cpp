// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GA_FightBack.h"

#include "Actor/EffectActor.h"


void UGA_FightBack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if(!CommitAbility(Handle,ActorInfo,ActivationInfo))
	{
		CancelAbility(Handle,ActorInfo,ActivationInfo,true);
		return;
	}

	CommitAbilityCooldown(Handle,ActorInfo,ActivationInfo,false);

	SpawnProjectile();
	
	EndAbility(Handle,ActorInfo,ActivationInfo,true,false);
}

void UGA_FightBack::SpawnProjectile() const
{
	if(const AActor* Avatar=GetAvatarActorFromActorInfo())
	{
		FVector ActorLocation=Avatar->GetActorLocation();
		const float AngleStep=360.f/ProjectileNum;
		const FVector HeightOffset(0, 0, 50.0f);
		UWorld* World=GetWorld();
		for (int32 i=0;i<ProjectileNum;i++)
		{
			const float CurrentAngle=AngleStep*i;
			const FVector Direction=FVector(FMath::Cos(FMath::DegreesToRadians(CurrentAngle)),
											FMath::Sin(FMath::DegreesToRadians(CurrentAngle)),
											0).GetSafeNormal();
				
			const FVector SpawnPosition=ActorLocation+Direction*SpawnRadius;

			const FRotator SpawnRotation=Direction.Rotation();

			AEffectActor* Projectile=World->SpawnActor<AEffectActor>(ProjectileClass,SpawnPosition,SpawnRotation);

			if(IsValid(Projectile))
			{
				Projectile->SetLevel(CurrentSkillLevel);
			}
		}
	}
}
