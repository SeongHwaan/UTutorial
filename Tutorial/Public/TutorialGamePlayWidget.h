// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tutorial.h"
#include "Blueprint/UserWidget.h"
#include "TutorialGamePlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API UTutorialGamePlayWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnResumeClicked();

	UFUNCTION()
	void OnReturnToTitleClicked();

	UFUNCTION()
	void OnRetryGameClicked();

protected:

	UPROPERTY()
	TObjectPtr<class UButton> ResumeButton;

	UPROPERTY()
	TObjectPtr<class UButton> ReturnToTitleButton;

	UPROPERTY()
	TObjectPtr<class UButton> RetryGameButton;
};
