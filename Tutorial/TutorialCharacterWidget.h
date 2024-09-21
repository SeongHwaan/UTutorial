// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tutorial.h"
#include "Blueprint/UserWidget.h"
#include "TutorialCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API UTutorialCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(TObjectPtr<class UTutorialCharacterStatComponent> NewCharacterStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

private:
	TWeakObjectPtr<class UTutorialCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
	TObjectPtr<class UProgressBar> HPProgressBar;
};
