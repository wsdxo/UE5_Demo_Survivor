// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UAuraGameplayAbility;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AAuraPlayerController();

	UPROPERTY(EditAnywhere,BlueprintType,Category="Ability Infos")
	TMap<UAuraGameplayAbility*,int32>Ability2Level;
	UPROPERTY(EditAnywhere,BlueprintType,Category="Ability Infos")
	TArray<TSubclassOf<UAuraGameplayAbility>>AbilitiesToGet;
	
	TPair<TArray<UAuraGameplayAbility*>,TArray<int32>>GetSkillUpgradeInfo();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext>AuraContext;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction>MoveAction;

	void Move(const FInputActionValue& InputActionValue);
};
