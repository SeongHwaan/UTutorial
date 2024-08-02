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

	ATutorialGameModeBase();

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
