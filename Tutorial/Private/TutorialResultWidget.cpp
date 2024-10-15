// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialResultWidget.h"
#include "Components/TextBlock.h"
#include "TutorialGameStateBase.h"

void UTutorialResultWidget::BindGameState(ATutorialGameStateBase* GameState)
{
	CHECK(GameState != nullptr);
	CurrentGameState = GameState;
}

void UTutorialResultWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CHECK(CurrentGameState.IsValid());

	auto Result = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtResult")));
	CHECK(Result != nullptr);
	Result->SetText(FText::FromString(CurrentGameState->IsGameCleared() ? TEXT("Mission Complete") : TEXT("Mission Failed")));

	auto TotalScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtTotalScore")));
	CHECK(TotalScore != nullptr);
	TotalScore->SetText(FText::FromString(FString::FromInt(CurrentGameState->GetTotalGameScore())));
}
