// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tutorial.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "TutorialGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FTutorialCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FTutorialCharacterData() : Level(1), MaxHP(100.0f), Attack(10.0f), DropExp(10), NextExp(30) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DropExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 NextExp;
};

/**
 * 
 */
UCLASS()
class TUTORIAL_API UTutorialGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
	UTutorialGameInstance();

	virtual void Init() override;
	FTutorialCharacterData* GetTutorialCharacterData(int32 Level);

	FStreamableManager StreamableManager;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CharacterData", Meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> TCharacterTable;
};
