// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"


AAuraCharacter::AAuraCharacter()
{
	CameraBoom=CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength=2000;
	CameraBoom->bUsePawnControlRotation=false;
	CameraBoom->SetRelativeRotation(FRotator(-80, 0, 0));
	CameraBoom->SetRelativeLocation(FVector(0,0,200));

	FollowCamera=CreateDefaultSubobject<UCameraComponent>("FollowComponent");
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->SetProjectionMode(ECameraProjectionMode::Perspective);
	FollowCamera->SetFieldOfView(55);
}
