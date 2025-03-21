// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/EffectActor.h"
#include "ProjectileTrack.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
/**
 * 
 */
UCLASS()
class AURA_API AProjectileTrack : public AEffectActor
{
	GENERATED_BODY()

public:
	AProjectileTrack();

	UFUNCTION()
	void SetHomingTarget(AActor* Target);

protected:
	UPROPERTY()
	TObjectPtr<AActor> HomingTarget;

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	void FindNearestEnemy();
};
