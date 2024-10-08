// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialGameStateBase.h"

ATutorialGameStateBase::ATutorialGameStateBase()
{
	TotalGameScore = 0;
}

int32 ATutorialGameStateBase::GetTotalGameScore() const
{
	return TotalGameScore;
}

void ATutorialGameStateBase::AddGameScore()
{
	TotalGameScore++;
}
