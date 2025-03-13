// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EnemySpawner.h"

#include "Game/AuraGameStateBase.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle,this,&AEnemySpawner::SpawnEnemy,SpwanInterval,true);

	Cast<AAuraGameStateBase>(GetWorld()->GetGameState())->EnemySpawners.Add(this);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnEnemy()
{
	AAuraGameStateBase* GameState = GetWorld()->GetGameState<AAuraGameStateBase>();
	if (!GameState || GameState->ActiveEnemies.Num() >= MaxEnemyCount) return;

	if (EnemyClass)
	{
		const FVector Location = GetActorLocation();
		if (AAuraEnemy* NewEnemy = GetWorld()->SpawnActor<AAuraEnemy>(EnemyClass, Location, FRotator::ZeroRotator))
		{
			NewEnemy->OnDestroyed.AddDynamic(this, &AEnemySpawner::OnEnemyDestroyed);
			GameState->AddEnemy(NewEnemy);
		}
	}
}

void AEnemySpawner::OnEnemyDestroyed(AActor* DestroyedActor)
{
	AAuraGameStateBase* GameState=GetWorld()->GetGameState<AAuraGameStateBase>();
	if(!GameState)return;
	if(AAuraEnemy* Enemy=Cast<AAuraEnemy>(DestroyedActor))
	{
		GameState->RemoveEnemy(Enemy);
	}
}

