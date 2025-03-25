// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EnemyProjectile.h"

#include "Character/AuraCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


AEnemyProjectile::AEnemyProjectile()
{
	Sphere=CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());

	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed=1500;
	ProjectileMovementComponent->MaxSpeed=1500;
	ProjectileMovementComponent->ProjectileGravityScale=0;
}

void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this,&AEnemyProjectile::OnSphereBeginOverlap);
	
	SetLifeSpan(10.f);
}

void AEnemyProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEnemyProjectile::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AAuraCharacter* PlayerCharacter=Cast<AAuraCharacter>(OtherActor))
	{
		ApplyEffectToTarget(PlayerCharacter,InstantGameplayEffectClass);
		Destroy();
	}
}
