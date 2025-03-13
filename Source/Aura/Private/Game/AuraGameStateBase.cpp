// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AuraGameStateBase.h"


void AAuraGameStateBase::AddEnemy(AAuraEnemy* Enemy)
{
	if(Enemy&&!ActiveEnemies.Contains(Enemy))
	{
		ActiveEnemies.Add(Enemy);
	}
}

void AAuraGameStateBase::RemoveEnemy(AAuraEnemy* Enemy)
{
	if (Enemy&&ActiveEnemies.Contains(Enemy))
	{
		ActiveEnemies.Remove(Enemy);
	}
}
