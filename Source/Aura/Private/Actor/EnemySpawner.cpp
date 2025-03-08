// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EnemySpawner.h"

#include "Kismet/KismetMathLibrary.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnArea=CreateDefaultSubobject<UBoxComponent>("SpawnArea");
	SetRootComponent(SpawnArea);
	SpawnArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle,this,&AEnemySpawner::SpawnEnemy,SpwanInterval,true);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnEnemy()
{
	if(ActiveEnemies.Num()>=MaxEnemyCount)return;

	if(EnemyClass)
	{
		FVector Origin = SpawnArea->Bounds.Origin;
		FVector Extent = SpawnArea->Bounds.BoxExtent;
		FVector Location = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);
        
		FRotator Rotation(0, FMath::RandRange(0, 360), 0);
        
		if(AAuraEnemy* NewEnemy = GetWorld()->SpawnActor<AAuraEnemy>(EnemyClass, Location, Rotation))
		{
			NewEnemy->OnDestroyed.AddDynamic(this, &AEnemySpawner::OnEnemyDestroyed);
			ActiveEnemies.Add(NewEnemy);
		}
		
	}
}

void AEnemySpawner::OnEnemyDestroyed(AActor* DestroyedActor)
{
	if(AAuraEnemy* Enemy=Cast<AAuraEnemy>(DestroyedActor))
	{
		ActiveEnemies.Remove(Enemy);
	}
}

