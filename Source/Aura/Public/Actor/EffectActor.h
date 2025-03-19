// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class AURA_API AEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Apply Effect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Apply Effect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Apply Effect")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor*TargetActor,TSubclassOf<UGameplayEffect>GameplayEffectClass);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetLevel(float InLevel);

	UFUNCTION()
	float GetEffectActorLevel()const{return Level;}

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent>Mesh;

	UPROPERTY()
	float Level=1;

	
	
};
