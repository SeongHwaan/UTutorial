// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TutorialCharacterSetting.generated.h"

/**
 * 
 */
UCLASS(config=Tutorial)
class TUTORIALSETTING_API UTutorialCharacterSetting : public UObject
{
	GENERATED_BODY()
	
public:
	UTutorialCharacterSetting();

	UPROPERTY(config)
	TArray<FSoftObjectPath> CharacterAssets;
};
