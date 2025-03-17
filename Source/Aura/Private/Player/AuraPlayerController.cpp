// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "Math/UnrealMathUtility.h"
#include "AbilitySystem/AuraGameplayAbility.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"



AAuraPlayerController::AAuraPlayerController()
{
	bReplicates=true;
}

TPair<TArray<UAuraGameplayAbility*>, TArray<int32>> AAuraPlayerController::GetSkillUpgradeInfo()
{
	int32 Index;

	TPair<TArray<UAuraGameplayAbility*>, TArray<int32>> Result;
	TArray<UAuraGameplayAbility*> Abilities;
	TArray<int32>Levels;
	for(int32 i=0;i<3;i++)
	{
		Index=FMath::RandRange(0,Ability2Level.Num()-1);
		UAuraGameplayAbility* Ability=AbilitiesToGet[Index].GetDefaultObject();
		Abilities.Add(Ability);
		Levels.Add(Ability2Level[Ability]);
	}
	Result={Abilities,Levels};
	return Result;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(AuraContext,0);

	bShowMouseCursor=true;
	DefaultMouseCursor=EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector=InputActionValue.Get<FVector2d>();
	const FRotator Rotation=GetControlRotation();
	const FRotator YawRotation=FRotator(0,Rotation.Yaw,0);

	const FVector ForwardDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* ControllerPawn=GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}
