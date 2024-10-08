// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialHUDWidget.h"
#include "TutorialCharacterStatComponent.h"
#include "TutorialPlayerState.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

//From Character, this function will be called (Not PlayerController because Character has CharacterStatComponent)
void UTutorialHUDWidget::BindCharacterStat(UTutorialCharacterStatComponent* CharacterStat)
{
	CHECK(CharacterStat != nullptr);
	CurrentCharacterStat = CharacterStat;
	CharacterStat->OnHPChanged.AddUObject(this, &UTutorialHUDWidget::UpdateCharacterStat);
}

//From PlayerController, this function will be called
void UTutorialHUDWidget::BindPlayerState(ATutorialPlayerState* PlayerState)
{
	CHECK(PlayerState != nullptr);
	CurrentPlayerState = PlayerState;
	PlayerState->OnPlayerStateChanged.AddUObject(this, &UTutorialHUDWidget::UpdatePlayerState);
}

void UTutorialHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbHP")));
	CHECK(HPBar != nullptr);

	ExpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbExp")));
	CHECK(ExpBar != nullptr);

	PlayerName = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtPlayerName")));
	CHECK(PlayerName != nullptr);

	PlayerLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtLevel")));
	CHECK(PlayerLevel != nullptr);

	CurrentScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurrentScore")));
	CHECK(CurrentScore != nullptr);

	HighScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtHighScore")));
	CHECK(HighScore != nullptr);
}

void UTutorialHUDWidget::UpdateCharacterStat()
{
	CHECK(CurrentCharacterStat.IsValid());

	HPBar->SetPercent(CurrentCharacterStat->GetHPRatio());
}

void UTutorialHUDWidget::UpdatePlayerState()
{
	CHECK(CurrentPlayerState.IsValid());

	ExpBar->SetPercent(CurrentPlayerState->GetExpRatio());
	PlayerName->SetText(FText::FromString(CurrentPlayerState->GetPlayerName()));
	PlayerLevel->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetCharacterLevel())));
	CurrentScore->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetGameScore())));
}
