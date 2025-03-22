// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/FightBack.h"

#include "Character/AuraEnemy.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


AFightBack::AFightBack()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere=CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
	
	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed=5000;
	ProjectileMovementComponent->MaxSpeed=5000;
	ProjectileMovementComponent->ProjectileGravityScale=0;
}

void AFightBack::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this,&AFightBack::OnSphereBeginOverlap);
	SetLifeSpan(15.f);
}

void AFightBack::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AAuraEnemy* Enemy = Cast<AAuraEnemy>(OtherActor))
	{
		ApplyEffectToTarget(Enemy, InstantGameplayEffectClass);
	}
}
