// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialCharacterSelectWidget.h"
#include "TutorialCharacterSetting.h"
#include "TutorialGameInstance.h"
#include "EngineUtils.h"
#include "Animation/SkeletalMeshActor.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "TutorialSaveGame.h"
#include "TutorialPlayerState.h"
#include "Kismet/GameplayStatics.h"


void UTutorialCharacterSelectWidget::NextCharacter(bool bForward)
{
	bForward ? CurrentIndex++ : CurrentIndex--;

	if (CurrentIndex == -1)
		CurrentIndex = MaxIndex - 1;
	if (CurrentIndex == MaxIndex)
		CurrentIndex = 0;

	auto CharacterSetting = GetDefault<UTutorialCharacterSetting>();
	auto AssetRef = CharacterSetting->CharacterAssets[CurrentIndex];

	auto TGameInstance = GetWorld()->GetGameInstance<UTutorialGameInstance>();
	CHECK(TGameInstance != nullptr);
	CHECK(TargetComponent.IsValid());

	USkeletalMesh* Asset = TGameInstance->StreamableManager.LoadSynchronous<USkeletalMesh>(AssetRef);

	if (Asset != nullptr)
		TargetComponent->SetSkeletalMesh(Asset);
}

void UTutorialCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentIndex = 0;
	auto CharacterSetting = GetDefault<UTutorialCharacterSetting>();
	MaxIndex = CharacterSetting->CharacterAssets.Num();

	//Find ASkeletalMeshActor in World
	for (TActorIterator<ASkeletalMeshActor> It(GetWorld()); It; ++It)
	{
		TargetComponent = It->GetSkeletalMeshComponent();
		break;
	}

	PrevButton = Cast<UButton>(GetWidgetFromName(TEXT("btnPrev")));
	CHECK(PrevButton != nullptr);

	NextButton = Cast<UButton>(GetWidgetFromName(TEXT("btnNext")));
	CHECK(NextButton != nullptr);

	TextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("edtPlayerName")));
	CHECK(TextBox != nullptr);

	ConfirmButton = Cast<UButton>(GetWidgetFromName(TEXT("btnConfirm")));
	CHECK(ConfirmButton != nullptr);

	PrevButton->OnClicked.AddDynamic(this, &UTutorialCharacterSelectWidget::OnPrevClicked);
	NextButton->OnClicked.AddDynamic(this, &UTutorialCharacterSelectWidget::OnNextClicked);
	ConfirmButton->OnClicked.AddDynamic(this, &UTutorialCharacterSelectWidget::OnConfirmClicked);
}

void UTutorialCharacterSelectWidget::OnPrevClicked()
{
	NextCharacter(false);
}

void UTutorialCharacterSelectWidget::OnNextClicked()
{
	NextCharacter(true);
}

void UTutorialCharacterSelectWidget::OnConfirmClicked()
{
	FString CharacterName = TextBox->GetText().ToString();
	if (CharacterName.Len() <= 0 || CharacterName.Len() >= 10)
		return;

	UTutorialSaveGame* NewPlayerData = NewObject<UTutorialSaveGame>();
	NewPlayerData->PlayerName = CharacterName;
	NewPlayerData->Level = 1;
	NewPlayerData->Exp = 0;
	NewPlayerData->HighScore = 0;
	NewPlayerData->CharacterIndex = CurrentIndex;

	auto TPlayerState = GetDefault<ATutorialPlayerState>();
	if (UGameplayStatics::SaveGameToSlot(NewPlayerData, TPlayerState->SaveSlotName, 0))
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("NewMap"));
	}
	else
	{
		LOG(Error, TEXT("SaveGame Error!"));
	}
}
