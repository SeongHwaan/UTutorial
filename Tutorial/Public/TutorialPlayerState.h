// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tutorial.h"
#include "GameFramework/PlayerState.h"
#include "TutorialPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnLevelUpDelegate);

/**
 * 
 */
UCLASS()
class TUTORIAL_API ATutorialPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ATutorialPlayerState();

	int32 GetGameScore() const;
	int32 GetGameHighScore() const;
	int32 GetCharacterLevel() const;
	int32 GetCharacterIndex() const;
	float GetExpRatio() const;
	bool AddExp(int32 IncomeExp);
	void AddGameScore();

	void InitPlayerData();
	void SavePlayerData();

	FString SaveSlotName;

protected:
	
	UPROPERTY(Transient)
	int32 GameScore;

	UPROPERTY(Transient)
	int32 GameHighScore;

	UPROPERTY(Transient)
	int32 CharacterLevel;

	UPROPERTY(Transient)
	int32 Exp;

	UPROPERTY(Transient)
	int32 CharacterIndex;

private:
	void SetCharacterLevel(int32 NewCharacterLevel);
	struct FTutorialCharacterData* CurrentStatData;

public:
	FOnPlayerStateChangedDelegate OnPlayerStateChanged;
	FOnLevelUpDelegate OnLevelUp;
};
