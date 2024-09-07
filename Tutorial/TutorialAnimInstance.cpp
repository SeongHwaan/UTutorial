// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UTutorialAnimInstance::UTutorialAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	IsDead = false;
}

void UTutorialAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn))
		return;

	if (!IsDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}
}

void UTutorialAnimInstance::PlayAttackMontage()
{
	CHECK(!IsDead);
	Montage_Play(AttackMontage, 1.0f);
}

void UTutorialAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	CHECK(!IsDead);
	CHECK(Montage_IsPlaying(AttackMontage));
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
}

void UTutorialAnimInstance::SetDeadAnim()
{
	IsDead = true;
}

void UTutorialAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}

void UTutorialAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

FName UTutorialAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	CHECK(FMath::IsWithinInclusive<int32>(Section, 1, 4), NAME_None);
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}
