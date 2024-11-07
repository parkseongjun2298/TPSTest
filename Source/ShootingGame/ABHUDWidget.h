// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootingGame.h"
#include "Blueprint/UserWidget.h"
#include "ABHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API UABHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(class UABPlayerStatComponent* CharacterStat);

	
	void BindPlayerState(class AABPlayerState* PlayerState);

protected:
	virtual void NativeConstruct()override;
	void UpdateCharacterStat();

	UFUNCTION()
	void UpdatePlayerState();

private:

	UPROPERTY()
	class UTextBlock* PlayerName;

	UPROPERTY()
	class UTextBlock* MaxBullet;

	UPROPERTY()
	class UTextBlock* CurBullet;

	UPROPERTY()
	class UProgressBar* HPBar;

	UPROPERTY()
	class UProgressBar* EXPBar;


	TWeakObjectPtr<class UABPlayerStatComponent>CurCharacterStat;
	TWeakObjectPtr<class AABPlayerState>CurPlayerState;
};
