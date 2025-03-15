// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GA_LevelUp.h"

#include "Blueprint/UserWidget.h"
#include "Player/AuraPlayerController.h"


UGA_LevelUp::UGA_LevelUp()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_LevelUp::ShowLevelUpUI_Implementation()
{
	if(IsValid(LevelUpUIClass))
	{
		if(AAuraPlayerController* AuraPlayerController=Cast<AAuraPlayerController>(GetAvatarActorFromActorInfo()->GetInstigatorController()))
		{
			if(!LevelUpUIInstance)
			{
				LevelUpUIInstance=CreateWidget<UUserWidget>(AuraPlayerController,LevelUpUIClass,"LevelUpUI");
			}
			if(IsValid(LevelUpUIInstance))
			{
				LevelUpUIInstance->AddToViewport(200);

				FInputModeUIOnly InputMode;
				InputMode.SetWidgetToFocus(LevelUpUIInstance->TakeWidget());
				InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
				AuraPlayerController->SetInputMode(InputMode);
				AuraPlayerController->bShowMouseCursor=true;
			}
		}
	}
}


void UGA_LevelUp::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                  const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!HasAuthority(&ActivationInfo)) return;
	
	if(!CommitAbility(Handle,ActorInfo,ActivationInfo))
	{
		return;
	}

	AActor* Avatar=GetAvatarActorFromActorInfo();
	if(!Avatar)return;

	ShowLevelUpUI_Implementation();

	
	EndAbility(Handle,ActorInfo,ActivationInfo,true,false);
}
