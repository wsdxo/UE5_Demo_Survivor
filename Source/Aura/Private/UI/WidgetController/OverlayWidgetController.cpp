// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Character/AuraCharacter.h"


void UOverlayWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AuraAttributeSet=CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());

	OnXPPercentChanged.Broadcast(0);
	
}

void UOverlayWidgetController::BindCallBacksToDependencies()
{
	PlayerCharacterInstance->OnXPChangedDelegate.AddUObject(this,&UOverlayWidgetController::OnXPChanged);
	
	const UAuraAttributeSet* AuraAttributeSet=CastChecked<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()
		).AddUObject(this,&UOverlayWidgetController::HealthChanged);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()
		).AddUObject(this,&UOverlayWidgetController::MaxHealthChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data)const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data)const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::OnXPChanged(int32 NewXP)const
{
	const ULevelUpInfo* LevelUpInfo=PlayerCharacterInstance->LevelUpInfo;
	check(LevelUpInfo);

	const int32 Level=LevelUpInfo->FindLevelForXP(NewXP);
	const int32 MaxLevel=LevelUpInfo->LevelUpInfos.Num();

	if(Level>MaxLevel||Level<=0)return;

	const int32 LevelUpRequirement=LevelUpInfo->LevelUpInfos[Level].LevelUpRequirement;
	const int32 PreviousLevelRequirement=LevelUpInfo->LevelUpInfos[Level-1].LevelUpRequirement;

	const int32 DeltaLevelUpRequirement=LevelUpRequirement-PreviousLevelRequirement;
	const int32 XPForThisLevel=NewXP-PreviousLevelRequirement;

	const float XPBarPercent=static_cast<float>(XPForThisLevel)/static_cast<float>(DeltaLevelUpRequirement);

	OnXPPercentChanged.Broadcast(XPBarPercent);
	
}
