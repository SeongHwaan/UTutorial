// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tutorial.h"
#include "TutorialGamePlayWidget.h"
#include "TutorialResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API UTutorialResultWidget : public UTutorialGamePlayWidget
{
	GENERATED_BODY()

public:
	void BindGameState(class ATutorialGameStateBase* GameState);

protected:
	virtual void NativeConstruct() override;
	
private:
	TWeakObjectPtr<class ATutorialGameStateBase> CurrentGameState;
};
