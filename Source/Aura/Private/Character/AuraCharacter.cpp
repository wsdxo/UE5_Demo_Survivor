// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"


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
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState=GetPlayerState<AAuraPlayerState>();
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState,this);

	AbilitySystemComponent=AuraPlayerState->GetAbilitySystemComponent();

	AttributeSet=AuraPlayerState->GetAttributeSet();
}
