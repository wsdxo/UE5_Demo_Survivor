// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AuraGameModeBase.h"

#include "Actor/EnemySpawner.h"
#include "Character/AuraCharacter.h"
#include "Character/AuraEnemy.h"
#include "Game/AuraGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerController.h"


AAuraGameModeBase::AAuraGameModeBase()
{
	
}

void AAuraGameModeBase::ReStartGame()
{

	AAuraPlayerController* PlayerController=Cast<AAuraPlayerController>(UGameplayStatics::GetPlayerController(this,0));

	if(!PlayerController)return;
	
	if (APawn* OldPawn = PlayerController->GetPawn())
	{
		OldPawn->UnPossessed();
		OldPawn->Destroy();
	}
	AActor* PlayerStart = FindPlayerStart(PlayerController);
	RestartPlayerAtPlayerStart(PlayerController,FindPlayerStart(PlayerController));

	if (AAuraCharacter* NewCharacter = Cast<AAuraCharacter>(PlayerController->GetPawn()))
	{
		PlayerController->Possess(NewCharacter);
		
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor=false;
		
	}
	
	if(AAuraGameStateBase* AuraGameState=GetWorld()->GetGameState<AAuraGameStateBase>())
	{
		TArray<AAuraEnemy*> LocalActiveEnemies =  AuraGameState->ActiveEnemies;
		for (AAuraEnemy* Enemy : LocalActiveEnemies)
		{
			Enemy->Destroy();
		}
		for (AEnemySpawner* EnemySpawner : AuraGameState->EnemySpawners)
		{
			EnemySpawner->PrimaryActorTick.bCanEverTick=true;
		}
	}
}
