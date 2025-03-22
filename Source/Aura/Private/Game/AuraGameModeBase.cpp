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

	if(AAuraPlayerController* PlayerController=Cast<AAuraPlayerController>(UGameplayStatics::GetPlayerController(this,0)))
	{
		if (APawn* OldPawn = PlayerController->GetPawn())
		{
			OldPawn->UnPossessed();
			OldPawn->Destroy();
			GetWorld()->DestroyActor(OldPawn);
		}
		if(AActor* PlayerStart = FindPlayerStart(PlayerController))
		{
			RestartPlayerAtPlayerStart(PlayerController,FindPlayerStart(PlayerController));
		}
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
