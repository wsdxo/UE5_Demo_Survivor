// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/EffectActor.h"
#include "EnemyProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
/**
 * 
 */
UCLASS()
class AURA_API AEnemyProjectile : public AEffectActor
{
	GENERATED_BODY()

public:
	AEnemyProjectile();
	
protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent>Sphere;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent>ProjectileMovementComponent;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
