// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootingGame.h"
#include "GameFramework/PlayerState.h"
#include "ABPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangeDelegate);


/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API AABPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AABPlayerState();
	int32 GetMaxBullet();
	int32 GetCurBullet();
	void InitPlayerData();
	int32 GetCharLevel();

	void SetMaxBullet(int32 Bullet);
	void SetCurBullet(int32 Bullet);
	void ReLoadBullet(int32 Bullet);

	FOnPlayerStateChangeDelegate OnPlayerStateChange;
protected:
	UPROPERTY(Transient)
	int32 MaxBullet;

	UPROPERTY(Transient)
	int32 CurBullet;

	UPROPERTY(Transient)
	int32 CharLevel;

private:
	struct FABCharacterData* CurStatData;
};
