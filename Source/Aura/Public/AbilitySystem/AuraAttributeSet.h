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

class ULevelUpInfo;
/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UAuraAttributeSet();

	void InitAttributes();
	
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

	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,XP)
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_XP,BlueprintReadWrite)
	FGameplayAttributeData XP;
	

	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Level)
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_Level,BlueprintReadWrite)
	FGameplayAttributeData Level;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo>LevelUpInfo;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_XP(const FGameplayAttributeData& OldValue)const;

	UFUNCTION()
	void OnRep_Level(const FGameplayAttributeData& OldValue)const;

	UFUNCTION()
	float GetCharacterLevel();
	
};
