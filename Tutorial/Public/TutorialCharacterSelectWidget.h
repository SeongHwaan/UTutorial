// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tutorial.h"
#include "Blueprint/UserWidget.h"
#include "TutorialCharacterSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API UTutorialCharacterSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable)
	void NextCharacter(bool bForward = true);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	int32 CurrentIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	int32 MaxIndex;

	TWeakObjectPtr<USkeletalMeshComponent> TargetComponent;

protected:

	UPROPERTY()
	TObjectPtr<class UButton> PrevButton;

	UPROPERTY()
	TObjectPtr<class UButton> NextButton;

	UPROPERTY()
	TObjectPtr<class UEditableTextBox> TextBox;

	UPROPERTY()
	TObjectPtr<class UButton> ConfirmButton;

private:

	UFUNCTION()
	void OnPrevClicked();

	UFUNCTION()
	void OnNextClicked();

	UFUNCTION()
	void OnConfirmClicked();



};
