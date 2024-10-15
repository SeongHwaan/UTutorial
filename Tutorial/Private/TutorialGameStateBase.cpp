// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialGameStateBase.h"

ATutorialGameStateBase::ATutorialGameStateBase()
{
	TotalGameScore = 0;
	bGameCleared = false;
}

int32 ATutorialGameStateBase::GetTotalGameScore() const
{
	return TotalGameScore;
}

//Adding all player's score
void ATutorialGameStateBase::AddGameScore()
{
	TotalGameScore++;
}

void ATutorialGameStateBase::SetGameCleared()
{
	bGameCleared = true;
}

bool ATutorialGameStateBase::IsGameCleared() const
{
	return bGameCleared;
}
