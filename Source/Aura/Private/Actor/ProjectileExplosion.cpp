// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/ProjectileExplosion.h"

#include "Character/AuraEnemy.h"
#include "Components/SphereComponent.h"


AProjectileExplosion::AProjectileExplosion()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere=CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AProjectileExplosion::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this,&AProjectileExplosion::OnSphereBeginOverlap);
	Sphere->InitSphereRadius(RadiusOfLevels[GetEffectActorLevel()]);

	SetLifeSpan(0.1f);
}

void AProjectileExplosion::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	if(AAuraEnemy* Enemy=Cast<AAuraEnemy>(OtherActor))
	{
		ApplyEffectToTarget(Enemy,InstantGameplayEffectClass);
	}
}
