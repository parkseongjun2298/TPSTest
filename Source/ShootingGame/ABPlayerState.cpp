// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPlayerState.h"

AABPlayerState::AABPlayerState()
{
	CharLevel = 1;
	MaxBullet = 30;
	CurBullet = MaxBullet;

}

int32 AABPlayerState::GetMaxBullet()
{
	return MaxBullet;
}

int32 AABPlayerState::GetCurBullet()
{
	return CurBullet;
}

void AABPlayerState::InitPlayerData()
{
	SetPlayerName(TEXT("PSJ"));
	CharLevel = 1;
	MaxBullet = 30;
	CurBullet = MaxBullet;
}
