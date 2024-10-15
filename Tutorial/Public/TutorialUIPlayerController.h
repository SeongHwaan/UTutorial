// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tutorial.h"
#include "GameFramework/PlayerController.h"
#include "TutorialUIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API ATutorialUIPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> UIWidgetClass;

	UPROPERTY()
	TObjectPtr<class UUserWidget> UIWidgetInstance;
};
