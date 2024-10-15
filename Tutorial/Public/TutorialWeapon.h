// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tutorial.h"
#include "GameFramework/Actor.h"
#include "TutorialWeapon.generated.h"

UCLASS()
class TUTORIAL_API ATutorialWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATutorialWeapon();

	float GetAttackRange() const;
	float GetAttackDamage() const;
	float GetAttackModifier() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float AttackDamageMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float AttackDamageMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float AttackModifierMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float AttackModifierMax;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = "Attack")
	float AttackDamage;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = "Attack")
	float AttackModifier;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<USkeletalMeshComponent> Weapon;
};
