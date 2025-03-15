// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/ProjectileFireBall.h"

#include "AttributeSet.h"
#include "Character/AuraEnemy.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectileFireBall::AProjectileFireBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere=CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
	
	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed=1500;
	ProjectileMovementComponent->MaxSpeed=1500;
	ProjectileMovementComponent->ProjectileGravityScale=0;
}

// Called when the game starts or when spawned
void AProjectileFireBall::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this,&AProjectileFireBall::OnSphereBeginOverlap);

	SetLifeSpan(10);
}

// Called every frame
void AProjectileFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileFireBall::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AAuraEnemy* Enemy = Cast<AAuraEnemy>(OtherActor))
	{
		//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green,TEXT("命中敌人"));
		ApplyEffectToTarget(Enemy, InstantGameplayEffectClass);
		Destroy();
	}
}

