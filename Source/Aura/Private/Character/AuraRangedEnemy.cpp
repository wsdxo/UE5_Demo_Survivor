// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraRangedEnemy.h"

#include "Actor/EffectActor.h"
#include "GameFramework/PawnMovementComponent.h"


AAuraRangedEnemy::AAuraRangedEnemy()
{
	
}

void AAuraRangedEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle,this,&AAuraRangedEnemy::CheckDistanceToPlayer,0.1f,true);
}

void AAuraRangedEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(IsValid(PlayerPawn))
	{
		FRotator TargetRotation=(PlayerPawn->GetActorLocation()-GetActorLocation()).Rotation();
		TargetRotation.Pitch=0;
		SetActorRotation(FMath::RInterpTo(GetActorRotation(),TargetRotation,DeltaSeconds,10.f));
	}
}

void AAuraRangedEnemy::CheckDistanceToPlayer()
{
	if(!PlayerPawn)
	{
		return;
	}
	float DistanceToPlayer=FVector::Distance(PlayerPawn->GetActorLocation(),GetActorLocation());
	if(DistanceToPlayer<AttackRange&&!bIsInAttackRange)
	{
		bIsInAttackRange=true;
		GetMovementComponent()->StopMovementImmediately();
		StartAttack();
	}
	else if(DistanceToPlayer>AttackRange&&bIsInAttackRange)
	{
		bIsInAttackRange=false;
		StopAttack();
	}
}

void AAuraRangedEnemy::StartAttack()
{
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle,this,&AAuraRangedEnemy::ShootProjectile,AttackInterval,true);
}

void AAuraRangedEnemy::StopAttack()
{
	GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
}

void AAuraRangedEnemy::ShootProjectile()
{
	if(!IsValid((PlayerPawn))||!IsValid(ProjectileClass))
	{
		return;
	}
	FVector Direction=(PlayerPawn->GetActorLocation()-GetActorLocation()).GetSafeNormal();
	FVector SpawnPosition=GetActorLocation()+FVector(50.f,0,0);
	
	if(AEffectActor* Projectile=GetWorld()->SpawnActor<AEffectActor>(ProjectileClass,SpawnPosition,Direction.Rotation()))
	{
		Projectile->SetLevel(1);
	}
	
}
