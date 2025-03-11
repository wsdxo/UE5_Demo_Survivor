// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"



#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UAuraAttributeSet();
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxHealth)
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_MaxHealth,BlueprintReadWrite)
	FGameplayAttributeData MaxHealth;

	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Health)
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_Health,BlueprintReadWrite)
	FGameplayAttributeData Health;

	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Attack)
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FGameplayAttributeData Attack;

	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Defense)
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FGameplayAttributeData Defense;

	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Experience)
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FGameplayAttributeData Experience;

	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxExperience)
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FGameplayAttributeData MaxExperience;

	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxExperienceMultiplier)
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FGameplayAttributeData MaxExperienceMultiplier;

	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Level)
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FGameplayAttributeData Level;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue) const;
	
};
