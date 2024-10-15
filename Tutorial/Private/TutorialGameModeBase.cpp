// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialGameModeBase.h"
#include "TutorialCharacter.h"
#include "TutorialPlayerController.h"
#include "TutorialGameStateBase.h"
#include "TutorialPlayerState.h"
#include "EngineUtils.h"

ATutorialGameModeBase::ATutorialGameModeBase()
{
	//Set up on BluePrint
	//DefaultPawnClass
	//PlayerControllerClass
	//PlayerStateClass

	ScoreToClear = 1;
}

void ATutorialGameModeBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	TGameState = Cast<ATutorialGameStateBase>(GameState);
}

void ATutorialGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	//PostLogin starts
	Super::PostLogin(NewPlayer);
	//PostLogin ends after PlayerController::OnPossess

	auto TPlayerState = Cast<ATutorialPlayerState>(NewPlayer->PlayerState);
	CHECK(TPlayerState != nullptr);
	TPlayerState->InitPlayerData();
}

//Flow: 
// 1. Section call 'GameMode'
// 2. GameMode call 'GameState' & 'PlayerController'
// 3. PlayerController call 'PlayerState'
// GameState manages data across the game (multiple players)
// PlayerState only manages one player
void ATutorialGameModeBase::AddScore(ATutorialPlayerController* Player)
{
	//Assuming multiple players exist
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		const auto TPlayerController = Cast<ATutorialPlayerController>(It->Get());
		if ((TPlayerController != nullptr) && (Player == TPlayerController))
		{
			TPlayerController->AddGameScore();
			break;
		}
	}

	TGameState->AddGameScore();

	if (GetScore() >= ScoreToClear)
	{
		TGameState->SetGameCleared();

		for (TActorIterator<APawn> It(GetWorld()); It; ++It)
		{
			(*It)->TurnOff();
		}

		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It) {
			const auto TPlayerController = Cast<ATutorialPlayerController>(It->Get());
			if (TPlayerController != nullptr)
			{
				TPlayerController->ShowResultUI();
			}
		}
	}
}

int32 ATutorialGameModeBase::GetScore() const
{
	return TGameState->GetTotalGameScore();
}
