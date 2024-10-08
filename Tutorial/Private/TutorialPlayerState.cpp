// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialPlayerState.h"
#include "TutorialGameInstance.h"

ATutorialPlayerState::ATutorialPlayerState()
{
	CharacterLevel = 1;
	GameScore = 0;
	Exp = 0;
}

int32 ATutorialPlayerState::GetGameScore() const
{
	return GameScore;
}

int32 ATutorialPlayerState::GetCharacterLevel() const
{
	return CharacterLevel;
}

float ATutorialPlayerState::GetExpRatio() const
{
	if (CurrentStatData->NextExp <= KINDA_SMALL_NUMBER)
		return 0.0f;

	float Result = (float)Exp / (float)CurrentStatData->NextExp;
	LOG(Warning, TEXT("Ratio : %f, Current : %d, Next : %d"), Result, Exp, CurrentStatData->NextExp);
	return Result;
}

bool ATutorialPlayerState::AddExp(int32 IncomeExp)
{
	if (CurrentStatData->NextExp == -1)
		return false;

	bool DidLevelUp = false;
	Exp += IncomeExp;

	if (Exp >= CurrentStatData->NextExp)
	{
		Exp -= CurrentStatData->NextExp;
		SetCharacterLevel(CharacterLevel + 1);
		DidLevelUp = true;
	}

	OnPlayerStateChanged.Broadcast();
	return DidLevelUp;
}

void ATutorialPlayerState::AddGameScore()
{
	GameScore++;
	OnPlayerStateChanged.Broadcast();
}

void ATutorialPlayerState::InitPlayerData()
{
	SetPlayerName(TEXT("Ness"));
	SetCharacterLevel(5);
	GameScore = 0;
	Exp = 0;
}

void ATutorialPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
	auto TGameInstance = Cast<UTutorialGameInstance>(GetGameInstance());
	CHECK(TGameInstance != nullptr);

	CurrentStatData = TGameInstance->GetTutorialCharacterData(NewCharacterLevel);
	CHECK(CurrentStatData != nullptr);

	CharacterLevel = NewCharacterLevel;
}
