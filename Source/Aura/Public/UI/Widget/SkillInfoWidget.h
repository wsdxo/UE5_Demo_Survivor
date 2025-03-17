// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillInfoWidget.generated.h"

class UAuraGameplayAbility;
class UButton;
class USkillInfoData;
/**
 * 
 */
UCLASS()
class AURA_API USkillInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable)
	void UpdateDisplay(UAuraGameplayAbility* NewAbility, int32 NewLevel);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* SkillNameText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* SkillIconImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* LevelDescriptionText;
	

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAuraGameplayAbility> AuraGameplayAbility;
	
};
