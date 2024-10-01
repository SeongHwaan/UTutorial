// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialCharacterWidget.h"
#include "TutorialCharacterStatComponent.h"
#include "Components/ProgressBar.h"


void UTutorialCharacterWidget::BindCharacterStat(TObjectPtr<class UTutorialCharacterStatComponent> NewCharacterStat)
{
	CHECK(NewCharacterStat != nullptr);

	CurrentCharacterStat = NewCharacterStat;
	NewCharacterStat->OnHPChanged.AddUObject(this, &UTutorialCharacterWidget::UpdateHPWidget);
	NewCharacterStat->OnHPChanged.AddLambda([this]() -> void {
		if (CurrentCharacterStat.IsValid())
		{
			LOG(Warning, TEXT("HPRatio : %f"), CurrentCharacterStat->GetHPRatio());
		}
		else
			LOG(Warning, TEXT("Failed"));
		});
}

void UTutorialCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	CHECK(HPProgressBar != nullptr);
	UpdateHPWidget();
}

void UTutorialCharacterWidget::UpdateHPWidget()
{
	if (CurrentCharacterStat.IsValid())
	{
		if (HPProgressBar != nullptr)
		{
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
		}
	}
}
