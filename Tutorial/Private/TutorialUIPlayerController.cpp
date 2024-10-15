// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialUIPlayerController.h"
#include "Blueprint/UserWidget.h"

void ATutorialUIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CHECK(UIWidgetClass != nullptr);

	UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);
	CHECK(UIWidgetInstance != nullptr);

	//NativeConstruct would be called
	UIWidgetInstance->AddToViewport();

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
	SetInputMode(Mode);
	bShowMouseCursor = true;
}
