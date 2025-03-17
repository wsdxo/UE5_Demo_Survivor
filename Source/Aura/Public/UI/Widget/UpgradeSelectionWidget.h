// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UpgradeSelectionWidget.generated.h"

class UAuraGameplayAbility;
class USkillInfoData;
class USkillInfoWidget;
/**
 * 
 */
UCLASS()
class AURA_API UUpgradeSelectionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	TObjectPtr<USkillInfoWidget> Option1_Widget;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	TObjectPtr<USkillInfoWidget> Option2_Widget;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	TObjectPtr<USkillInfoWidget> Option3_Widget;
	
	UFUNCTION(BlueprintCallable)
	void PopulateOptions(TArray<UAuraGameplayAbility*>& Abilities, const TArray<int32>& CurrentLevels);
	
	UFUNCTION(BlueprintCallable)
	void OnSkillSelected(int32 SelectionIndex);
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateSkillInfo(USkillInfoData* InfoData, int32 CurrentLevel);
	
};
