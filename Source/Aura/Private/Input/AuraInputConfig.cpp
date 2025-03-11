// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AuraInputConfig.h"

#include "InputAction.h"


const UInputAction* UAuraInputConfig::FindInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FAuraInputAction& Action:AbilityInputActions)
	{
		if(Action.InputAction&&Action.InputTag==InputTag)
		{
			return Action.InputAction;
		}
	}
	return nullptr;
}
