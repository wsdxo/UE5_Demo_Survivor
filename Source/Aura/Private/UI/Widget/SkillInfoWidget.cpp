// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SkillInfoWidget.h"

#include "AbilitySystem/AuraGameplayAbility.h"
#include "AbilitySystem/Data/SkillInfoData.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


void USkillInfoWidget::UpdateDisplay(UAuraGameplayAbility* NewAbility, int32 NewLevel)
{
	if(!IsValid(NewAbility))
	{
		return;
	}
	AuraGameplayAbility=NewAbility;
	
	SkillNameText->SetText(NewAbility->SkillInfoData->SkillName);

	if(SkillIconImage)
	{
		SkillIconImage->SetBrushFromTexture(NewAbility->SkillInfoData->SkillIcon.LoadSynchronous());
	}

	FText Description =FText::GetEmpty();

	if(FText* FoundDescription =NewAbility->SkillInfoData->LevelDescriptions.Find(NewLevel))
	{
		Description=*FoundDescription;
	}

	LevelDescriptionText->SetText(Description);
}
