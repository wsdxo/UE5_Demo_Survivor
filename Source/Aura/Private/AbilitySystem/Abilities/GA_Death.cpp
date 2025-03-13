// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GA_Death.h"

#include "AbilitySystemComponent.h"
#include "Actor/EnemySpawner.h"
#include "Blueprint/UserWidget.h"
#include "Character/AuraCharacter.h"
#include "Character/AuraEnemy.h"
#include "Game/AuraGameStateBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"


UGA_Death::UGA_Death()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_Death::ShowDeathUI_Implementation()
{
	if(IsValid(DeathUIClass)&&!DeathUIInstance)
	{
		if(AAuraPlayerController* AuraPlayerController=Cast<AAuraPlayerController>(GetAvatarActorFromActorInfo()->GetInstigatorController()))
		{
			DeathUIInstance=CreateWidget<UUserWidget>(AuraPlayerController,DeathUIClass,"DeathUI");
			if(DeathUIInstance)
			{
				DeathUIInstance->AddToViewport(100);

				FInputModeUIOnly InputMode;
				InputMode.SetWidgetToFocus(DeathUIInstance->TakeWidget());
				InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
				AuraPlayerController->SetInputMode(InputMode);
				AuraPlayerController->bShowMouseCursor=true;
			}
		}
	}
}


void UGA_Death::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if(!CommitAbility(Handle,ActorInfo,ActivationInfo))
	{
		return;
	}
	AActor* Avatar=GetAvatarActorFromActorInfo();
	if(!Avatar)return;
	

	GetAbilitySystemComponentFromActorInfo()->CancelAllAbilities();

	if(Avatar->IsA(AAuraEnemy::StaticClass()))
	{
		Avatar->Destroy();
	}
	else if(Avatar->IsA(AAuraCharacter::StaticClass()))
	{
		//TODO: add player death later
		
		if(AAuraGameStateBase* AuraGameState=GetWorld()->GetGameState<AAuraGameStateBase>())
		{
			for(AEnemySpawner* EnemySpawner : AuraGameState->EnemySpawners)
			{
				EnemySpawner->PrimaryActorTick.bCanEverTick=false;
			}
		}

		ShowDeathUI_Implementation();
		Avatar->Destroy();
		
	}
	EndAbility(Handle,ActorInfo,ActivationInfo,true,false);
}
