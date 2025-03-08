// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"


class UAbilitySystemComponent;
class UAttributeSet;
UCLASS()
class AURA_API AAuraCharacterBase : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//TODO:Use GAS change this
	UPROPERTY(EditAnywhere,Category="Damage")
	float MaxHealth;
	UPROPERTY(EditAnywhere,Category="Damage")
	float CurrentHealth;

	UPROPERTY(EditAnywhere,Category="Damage")
	float Attack;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void TakeDamage(float AttackValue);

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Ability")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Ability")
	UAttributeSet* AttributeSet;
private:
};
