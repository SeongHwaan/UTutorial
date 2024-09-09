// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialItemBox.h"
#include "TutorialWeapon.h"
#include "TutorialCharacter.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ATutorialItemBox::ATutorialItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));

	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);
	Effect->SetupAttachment(RootComponent);

	Trigger->SetCollisionProfileName(TEXT("ItemBox"));
	Box->SetCollisionProfileName(TEXT("NoCollision"));

	WeaponItemClass = ATutorialWeapon::StaticClass();
}

// Called when the game starts or when spawned
void ATutorialItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATutorialItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATutorialItemBox::OnCharacterOverlap);
}

// Called every frame
void ATutorialItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATutorialItemBox::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	LOG_S(Warning);

	auto TCharacter = Cast<ATutorialCharacter>(OtherActor);
	CHECK(TCharacter != nullptr);

	if (TCharacter != nullptr && WeaponItemClass != nullptr)
	{
		if (TCharacter->CanSetWeapon())
		{
			auto NewWeapon = GetWorld()->SpawnActor<ATutorialWeapon>(WeaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
			TCharacter->SetWeapon(NewWeapon);
			Effect->Activate(true);
			//Hide until effect occurs
			Box->SetHiddenInGame(true, true);
			SetActorEnableCollision(false);
			Effect->OnSystemFinished.AddDynamic(this, &ATutorialItemBox::OnEffectFinished);
		}																				
		else
		{
			LOG(Warning, TEXT("%s can't equip weapon currently."), *TCharacter->GetName());
		}
	}

}

void ATutorialItemBox::OnEffectFinished(UParticleSystemComponent* PSystem)
{
	Destroy();
}

