// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tutorial.h"
#include "GameFramework/GameModeBase.h"
#include "TutorialGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API ATutorialGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	ATutorialGameModeBase();

	virtual void PostInitializeComponents() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	void AddScore(class ATutorialPlayerController* Player);

private:
	UPROPERTY()
	TObjectPtr<class ATutorialGameStateBase> TGameState;
};

