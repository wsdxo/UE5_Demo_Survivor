// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"

#include <ThirdParty/Breakpad/src/third_party/llvm/cxxabi.h>

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Abilities/GA_Death.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"


AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	CameraBoom=CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength=2000;
	CameraBoom->bUsePawnControlRotation=false;
	CameraBoom->SetRelativeRotation(FRotator(-90, 0, 0));
	CameraBoom->SetRelativeLocation(FVector(0,0,200));
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;

	FollowCamera=CreateDefaultSubobject<UCameraComponent>("FollowComponent");
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->SetProjectionMode(ECameraProjectionMode::Perspective);
	FollowCamera->SetFieldOfView(55);
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}



void AAuraCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	for (const FGameplayAbilitySpec& Spec:GetAbilitySystemComponent()->GetActivatableAbilities())
	{
		UGameplayAbility* Ability=Spec.Ability;
		if (Ability&&!Spec.IsActive())
		{
			if(!Ability->IsA(UGA_Death::StaticClass()))
				GetAbilitySystemComponent()->TryActivateAbility(Spec.Handle);
		}
	}
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState=GetPlayerState<AAuraPlayerState>();
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState,this);

	AbilitySystemComponent=AuraPlayerState->GetAbilitySystemComponent();

	AttributeSet=AuraPlayerState->GetAttributeSet();

	Cast<UAuraAttributeSet>(AttributeSet)->InitAttributes();

	if(AAuraPlayerController* AuraPlayerController=Cast<AAuraPlayerController>(GetController()))
	{
		if(AAuraHUD* AuraHUD=Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlay(AuraPlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet,this);
		}
	}

}
