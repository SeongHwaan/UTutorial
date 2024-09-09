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
}

// Called when the game starts or when spawned
void ATutorialWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATutorialWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

