// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tutorial.h"
#include "GameFramework/SaveGame.h"
#include "TutorialSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API UTutorialSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UTutorialSaveGame();

	UPROPERTY()
	int32 Level;

	UPROPERTY()
	int32 Exp;

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	int32 HighScore;
};
