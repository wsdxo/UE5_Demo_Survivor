// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelUpInfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraLevelUpInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 LevelUpRequirement;

	UPROPERTY(EditDefaultsOnly)
	int32 AttributePointAward=10;

	UPROPERTY(EditDefaultsOnly)
	int32 SkillPointAward=1;
	
};

/**
 * 
 */
UCLASS()
class AURA_API ULevelUpInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FAuraLevelUpInfo>LevelUpInfos;


	int32 FindLevelForXP(int32 XP)const;
	
	
	
};
