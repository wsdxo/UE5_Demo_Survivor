// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/UpgradeSelectionWidget.h"

#include "AbilitySystem/AuraGameplayAbility.h"
#include "Components/Button.h"
#include "Player/AuraPlayerController.h"
#include "UI/Widget/SkillInfoWidget.h"


void UUpgradeSelectionWidget::PopulateOptions(TArray<UAuraGameplayAbility*>& Abilities,
                                              const TArray<int32>& CurrentLevels)
{
	TArray<USkillInfoWidget*>AllOpotions={Option1_Widget,Option2_Widget,Option3_Widget};

	for(int32 i=0;i<AllOpotions.Num();i++)
	{
		if(Abilities.IsValidIndex(i)&&CurrentLevels.IsValidIndex((i)))
		{
			if(AllOpotions[i])
			{
				AllOpotions[i]->UpdateDisplay(Abilities[i],CurrentLevels[i]);
			}
		}
	}
}

void UUpgradeSelectionWidget::OnSkillSelected(int32 SelectionIndex)
{
	if(SelectionIndex<0||SelectionIndex>2)
	{
		return;
	}
	//TODO: Skill Level Up
	switch (SelectionIndex)
	{
		case 0:
			Option1_Widget->AuraGameplayAbility->UpgradeAbility();
			break;
		case 1:
			Option2_Widget->AuraGameplayAbility->UpgradeAbility();
			break;
		case 2:
			Option3_Widget->AuraGameplayAbility->UpgradeAbility();
			break;
	}
	RemoveFromParent();
}
