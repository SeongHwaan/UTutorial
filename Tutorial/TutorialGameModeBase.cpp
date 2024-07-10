// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialGameModeBase.h"
#include "TutorialPawn.h"
#include "TutorialPlayerController.h"

ATutorialGameModeBase::ATutorialGameModeBase()
{
	DefaultPawnClass = ATutorialPawn::StaticClass();
	PlayerControllerClass = ATutorialPlayerController::StaticClass();
}

void ATutorialGameModeBase::PostLogin(ATutorialPlayerController* NewPlayer)
{
	ABLOG(Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	ABLOG(Warning, TEXT("PostLogin End"));
}

