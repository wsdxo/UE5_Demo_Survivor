// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/LevelUpInfo.h"


int32 ULevelUpInfo::FindLevelForXP(int32 XP)const
{
	int32 Level=1;
	bool bSearching=true;
	while (bSearching)
	{
		if(LevelUpInfos.Num()<Level)
		{
			return Level;
		}
		if(XP>=LevelUpInfos[Level].LevelUpRequirement)
		{
			Level++;
		}
		else
		{
			bSearching=false;
		}
	}
	
	return Level;
}
