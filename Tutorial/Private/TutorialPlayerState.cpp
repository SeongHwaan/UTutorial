// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialPlayerState.h"
#include "TutorialGameInstance.h"
#include "TutorialSaveGame.h"
#include "Kismet/GameplayStatics.h"

ATutorialPlayerState::ATutorialPlayerState()
{
	CharacterLevel = 1;
	GameScore = 0;
	GameHighScore = 0;
	Exp = 0;
	SaveSlotName = TEXT("Player1");
	CharacterIndex = 0;
}

int32 ATutorialPlayerState::GetGameScore() const
{
	return GameScore;
}

int32 ATutorialPlayerState::GetGameHighScore() const
{
	return GameHighScore;
}

int32 ATutorialPlayerState::GetCharacterLevel() const
{
	return CharacterLevel;
}

int32 ATutorialPlayerState::GetCharacterIndex() const
{
	return CharacterIndex;
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
		OnLevelUp.Broadcast();
	}

	OnPlayerStateChanged.Broadcast();
	SavePlayerData();
	return DidLevelUp;
}

void ATutorialPlayerState::AddGameScore()
{
	GameScore++;
	if (GameScore > GameHighScore)
	{
		GameHighScore = GameScore;
	}
	OnPlayerStateChanged.Broadcast();
	SavePlayerData();
}

void ATutorialPlayerState::InitPlayerData()
{
	auto TSaveGame = Cast<UTutorialSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (TSaveGame == nullptr)
	{
		//New save file
		TSaveGame = GetMutableDefault<UTutorialSaveGame>();
	}

	SetPlayerName(TSaveGame->PlayerName);
	SetCharacterLevel(TSaveGame->Level);
	GameScore = 0;
	GameHighScore = TSaveGame->HighScore;
	Exp = TSaveGame->Exp;
	CharacterIndex = TSaveGame->CharacterIndex;

	SavePlayerData();
}

void ATutorialPlayerState::SavePlayerData()
{
	UTutorialSaveGame* NewPlayerData = NewObject<UTutorialSaveGame>();
	NewPlayerData->PlayerName = GetPlayerName();
	NewPlayerData->Level = CharacterLevel;
	NewPlayerData->Exp = Exp;
	NewPlayerData->HighScore = GameHighScore;
	NewPlayerData->CharacterIndex = CharacterIndex;

	if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0))
	{
		LOG(Error, TEXT("SaveGame Error"));
	}
}

void ATutorialPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
	auto TGameInstance = Cast<UTutorialGameInstance>(GetGameInstance());
	CHECK(TGameInstance != nullptr);

	CurrentStatData = TGameInstance->GetTutorialCharacterData(NewCharacterLevel);
	CHECK(CurrentStatData != nullptr);

	CharacterLevel = NewCharacterLevel;
}
