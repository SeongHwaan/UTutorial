// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tutorial.h"
#include "GameFramework/GameStateBase.h"
#include "TutorialGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API ATutorialGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	
	ATutorialGameStateBase();

	int32 GetTotalGameScore() const;
	void AddGameScore();

	void SetGameCleared();
	bool IsGameCleared() const;

private:
	UPROPERTY(Transient)
	int32 TotalGameScore;

	UPROPERTY(Transient)
	bool bGameCleared;
};
