// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "Blueprint/UserWidget.h"


void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget=CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	Widget->AddToViewport();
}
