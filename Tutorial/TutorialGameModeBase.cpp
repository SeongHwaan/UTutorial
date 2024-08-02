// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialGameModeBase.h"
#include "TutorialCharacter.h"
#include "TutorialPlayerController.h"

ATutorialGameModeBase::ATutorialGameModeBase()
{
}

void ATutorialGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	LOG(Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	LOG(Warning, TEXT("PostLogin End"));
}
