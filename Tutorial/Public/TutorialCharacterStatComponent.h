// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tutorial.h"
#include "Components/ActorComponent.h"
#include "TutorialCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnLevelUpDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TUTORIAL_API UTutorialCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTutorialCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:	
	void SetNewLevel(int32 NewLevel);
	void SetDamage(float NewDamage);
	void SetHP(float NewHP);
	float GetAttack() const;
	float GetHPRatio() const;
	int32 GetDropExp() const;

	FOnHPIsZeroDelegate OnHPIsZero;
	FOnHPChangedDelegate OnHPChanged;
	FOnLevelUpDelegate OnLevelUp;

private:
	struct FTutorialCharacterData* CurrentStatData;

	UPROPERTY(EditInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	int32 Level;

	//Transient: To exclude from serialization
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	float CurrentHP;

		
};
