// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "AuraEnemy.generated.h"

class UGameplayEffect;
/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraEnemy();
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)

	void ApplyEffectToTarget(AActor* TargetActor,TSubclassOf<UGameplayEffect> GameplayEffectClass);
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Apply Effect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffect;



	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float MoveSpeed = 500.0f;

	UPROPERTY(EditDefaultsOnly,Category="XP Award")
	int32 XPAward=50;


private:
	UFUNCTION()
	void OnCollisionBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult& SweepResult);

	APawn* PlayerPawn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AAIController>EnemyControllerClass;

public:
	virtual void AddCharacterAbilities() override;

	UFUNCTION(BlueprintCallable)
	int32 GetXPAward() const { return XPAward; }
	
};
