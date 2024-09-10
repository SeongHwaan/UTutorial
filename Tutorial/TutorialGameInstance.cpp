// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialGameInstance.h"

UTutorialGameInstance::UTutorialGameInstance()
{
	//CHECK(TCharacterTable->GetRowMap().Num() > 0);
}

void UTutorialGameInstance::Init()
{
	Super::Init();
	LOG(Warning, TEXT("DropExp of Level 20 TCharacter: %d"), GetTutorialCharacterData(20)->DropExp);
}

FTutorialCharacterData* UTutorialGameInstance::GetTutorialCharacterData(int32 Level)
{
	return TCharacterTable->FindRow<FTutorialCharacterData>(*FString::FromInt(Level), TEXT(""));
}
