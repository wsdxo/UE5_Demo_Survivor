// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/EffectActor.h"
#include "ProjectileExplosion.generated.h"

class USphereComponent;
/**
 * 
 */
UCLASS()
class AURA_API AProjectileExplosion : public AEffectActor
{
	GENERATED_BODY()

public:

	AProjectileExplosion();
	
	UPROPERTY(EditDefaultsOnly,Category="GameplayAbility")
	TArray<int32>RadiusOfLevels;

protected:
	virtual void BeginPlay() override;
	
private:
	TObjectPtr<USphereComponent>Sphere;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
};
