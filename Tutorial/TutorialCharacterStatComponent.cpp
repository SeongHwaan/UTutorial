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
		CurrentHP = CurrentStatData->MaxHP;
	}
	else
	{
		LOG(Error, TEXT("Level (%d) data doesn't exist"), NewLevel);
	}
}

void UTutorialCharacterStatComponent::SetDamage(float NewDamage)
{
	CHECK(CurrentStatData != nullptr);
	CurrentHP = FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP);

	if (CurrentHP <= 0.0f)
	{
		OnHPIsZero.Broadcast();
	}
}

float UTutorialCharacterStatComponent::GetAttack()
{
	//CHECK(CurrentStatData != nullptr);
	return CurrentStatData->Attack;
}

