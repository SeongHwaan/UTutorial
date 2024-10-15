// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialGamePlayWidget.h"
#include "Components/Button.h"
#include "TutorialPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UTutorialGamePlayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton = Cast<UButton>(GetWidgetFromName(TEXT("btnResume")));
	if (ResumeButton != nullptr)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UTutorialGamePlayWidget::OnResumeClicked);
	}

	ReturnToTitleButton = Cast<UButton>(GetWidgetFromName(TEXT("btnReturnToTitle")));
	if (ReturnToTitleButton != nullptr)
	{
		ReturnToTitleButton->OnClicked.AddDynamic(this, &UTutorialGamePlayWidget::OnReturnToTitleClicked);
	}

	RetryGameButton = Cast<UButton>(GetWidgetFromName(TEXT("btnRetryGame")));
	if (RetryGameButton != nullptr)
	{
		RetryGameButton->OnClicked.AddDynamic(this, &UTutorialGamePlayWidget::OnRetryGameClicked);
	}
}

void UTutorialGamePlayWidget::OnResumeClicked()
{
	auto TPlayerController = Cast<ATutorialPlayerController>(GetOwningPlayer());
	CHECK(TPlayerController != nullptr);

	RemoveFromParent();
	TPlayerController->ChangeInputMode(true);
	TPlayerController->SetPause(false);
}

void UTutorialGamePlayWidget::OnReturnToTitleClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Title"));
}

void UTutorialGamePlayWidget::OnRetryGameClicked()
{
	auto TPlayerController = Cast<ATutorialPlayerController>(GetOwningPlayer());
	CHECK(TPlayerController != nullptr);
	TPlayerController->RestartLevel();
}
