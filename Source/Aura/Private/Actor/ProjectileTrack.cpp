// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/ProjectileTrack.h"

#include "Character/AuraEnemy.h"
#include "Components/SphereComponent.h"
#include "Game/AuraGameStateBase.h"
#include "GameFramework/ProjectileMovementComponent.h"


AProjectileTrack::AProjectileTrack()
{
	PrimaryActorTick.bCanEverTick = true;
	Sphere=CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());

	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->bIsHomingProjectile=true;
	ProjectileMovementComponent->HomingAccelerationMagnitude=2000.f;
	ProjectileMovementComponent->InitialSpeed=500.f;
}

void AProjectileTrack::SetHomingTarget(AActor* Target)
{
	if(Target&&ProjectileMovementComponent)
	{
		HomingTarget=Target;
		AAuraEnemy* Enemy=Cast<AAuraEnemy>(HomingTarget);
		if(Enemy&&Enemy->HomingAnchor)
		{
			ProjectileMovementComponent->HomingTargetComponent=Enemy->HomingAnchor;

			ProjectileMovementComponent->bIsHomingProjectile=true;
		}
	}
}

void AProjectileTrack::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AAuraEnemy* Enemy=Cast<AAuraEnemy>(HomingTarget);
	if(!HomingTarget&&ProjectileMovementComponent)
	{
		FindNearestEnemy();
	}
}

void AProjectileTrack::BeginPlay()
{
	Super::BeginPlay();
	FindNearestEnemy();
	SetLifeSpan(10.f);
}

void AProjectileTrack::FindNearestEnemy()
{
	AActor* NearestEnemy = nullptr;
	float NearestDistance = FLT_MAX;
	FVector ProjectileLocation = GetActorLocation();

	if (AAuraGameStateBase* AuraGameState=Cast<AAuraGameStateBase>(GetWorld()->GetGameState()))
	{
		for(AAuraEnemy* Enemy:AuraGameState->ActiveEnemies)
		{
			float Distance=FVector::Distance(ProjectileLocation,Enemy->GetActorLocation());
			if(Distance<NearestDistance)
			{
				NearestDistance=Distance;
				NearestEnemy=Enemy;
			}
		}
		
	}

	if(NearestEnemy)
	{
		SetHomingTarget(NearestEnemy);
	}
	else
	{
		Destroy();
	}
}
