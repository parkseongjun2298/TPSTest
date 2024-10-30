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
	void BindCharacterStat();

protected:
	virtual void NativeConstruct()override;
	void UpdateCharacterStat();
	void UpdatePlayerState();

private:

	UPROPERTY()
	class UTextBlock* PlayerName;

	UPROPERTY()
	class UTextBlock* MaxBullet;

	UPROPERTY()
	class UTextBlock* CurBullet;

};
