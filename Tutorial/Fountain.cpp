// Fill out your copyright notice in the Description page of Project Settings.


#include "Fountain.h"

// Sets default values
AFountain::AFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//UStaticMeshComponent�� instance�� ���� ��. UStaticMesh�� Mesh �Ӽ��� ���� ��. �ϳ��� ��ü�� ����
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Water"));
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	Splash = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Splash"));

	RootComponent = Body;
	Water->SetupAttachment(Body);
	Light->SetupAttachment(Body);
	Splash->SetupAttachment(Body);

	Rotation = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotation"));
	RotateSpeed = 30.f;
	Rotation->RotationRate = FRotator(0.f, RotateSpeed, 0.f);
}

// Called when the game starts or when spawned
void AFountain::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

