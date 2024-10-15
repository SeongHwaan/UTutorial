// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialWeapon.h"

// Sets default values
ATutorialWeapon::ATutorialWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon;
	
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));

	AttackRange = 150.0f;
	AttackDamageMin = -2.5f;
	AttackDamageMax = 10.0f;
	AttackModifierMin = 0.85f;
	AttackModifierMax = 1.25f;
}

float ATutorialWeapon::GetAttackRange() const
{
	return AttackRange;
}

float ATutorialWeapon::GetAttackDamage() const
{
	return AttackDamage;
}

float ATutorialWeapon::GetAttackModifier() const
{
	return AttackModifier;
}

// Called when the game starts or when spawned
void ATutorialWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	AttackDamage = FMath::RandRange(AttackDamageMin, AttackDamageMax);
	AttackModifier = FMath::RandRange(AttackModifierMin, AttackModifierMax);

	LOG(Warning, TEXT("Weapon Damage : %f, Modifier : %f"), AttackDamage, AttackModifier);
}

// Called every frame
void ATutorialWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

