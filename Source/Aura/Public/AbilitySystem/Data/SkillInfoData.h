// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SkillInfoData.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API USkillInfoData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill UI")
	FText SkillName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill UI")
	FText SkillDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill UI")
	TMap<int32, FText> LevelDescriptions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill UI")
	TSoftObjectPtr<UTexture2D> SkillIcon;
	
	
};
