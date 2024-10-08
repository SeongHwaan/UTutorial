// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialCharacterStatComponent.h"
#include "TutorialGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTutorialCharacterStatComponent::UTutorialCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	CurrentStatData = nullptr;
	Level = 1;
	CurrentHP = 0;
	// ...
}


// Called when the game starts
void UTutorialCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTutorialCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
}

void UTutorialCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	auto TGameInstance = Cast<UTutorialGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	CHECK(TGameInstance != nullptr);
	CurrentStatData = TGameInstance->GetTutorialCharacterData(NewLevel);

	if (CurrentStatData != nullptr)
	{
		Level = NewLevel;
		SetHP(CurrentStatData->MaxHP);
	}
	else
	{
		LOG(Error, TEXT("Level (%d) data doesn't exist"), NewLevel);
	}
}

void UTutorialCharacterStatComponent::SetDamage(float NewDamage)
{
	CHECK(CurrentStatData != nullptr);
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP));
}

void UTutorialCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

float UTutorialCharacterStatComponent::GetAttack() const
{
	//CHECK(CurrentStatData != nullptr);
	return CurrentStatData->Attack;
}

float UTutorialCharacterStatComponent::GetHPRatio() const
{
	//CHECK(CurrentStatData != nullptr);
	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStatData->MaxHP);
}

int32 UTutorialCharacterStatComponent::GetDropExp() const
{
	return CurrentStatData->DropExp;
}

