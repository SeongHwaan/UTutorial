// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tutorial.h"
#include "Blueprint/UserWidget.h"
#include "TutorialHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API UTutorialHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindCharacterStat(class UTutorialCharacterStatComponent* CharacterStat);
	void BindPlayerState(class ATutorialPlayerState* PlayerState);

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterStat();
	void UpdatePlayerState();

private:
	TWeakObjectPtr<class UTutorialCharacterStatComponent> CurrentCharacterStat;
	TWeakObjectPtr<class ATutorialPlayerState> CurrentPlayerState;

	UPROPERTY()
	TObjectPtr<class UProgressBar> HPBar;
	
	UPROPERTY()
	TObjectPtr<class UProgressBar> ExpBar;

	UPROPERTY()
	TObjectPtr<class UTextBlock> PlayerName;

	UPROPERTY()
	TObjectPtr<class UTextBlock> PlayerLevel;

	UPROPERTY()
	TObjectPtr<class UTextBlock> CurrentScore;

	UPROPERTY()
	TObjectPtr<class UTextBlock> HighScore;

};
