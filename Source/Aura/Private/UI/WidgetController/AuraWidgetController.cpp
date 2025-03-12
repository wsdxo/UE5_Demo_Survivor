// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AuraWidgetController.h"


FWidgetControllerParams::FWidgetControllerParams()
{
	
}

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams)
{
	PlayerController=WidgetControllerParams.PlayerController;
	PlayerState=WidgetControllerParams.PlayerState;
	AbilitySystemComponent=WidgetControllerParams.AbilitySystemComponent;
	AttributeSet=WidgetControllerParams.AttributeSet;
}

void UAuraWidgetController::BroadcastInitialValues()
{
	
}

void UAuraWidgetController::BindCallBacksToDependencies()
{
	
}
