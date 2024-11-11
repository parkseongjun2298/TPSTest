// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPlayerState.h"
#include"ABGameInstance.h"
AABPlayerState::AABPlayerState()
{
	

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
	SetCharacterLevel(1);
	
	MaxBullet = 30;
	CurBullet = MaxBullet;

}

int32 AABPlayerState::GetCharLevel()
{
	return CharLevel;
}

void AABPlayerState::SetMaxBullet(int32 Bullet)
{
	MaxBullet = Bullet;
	OnPlayerStateChange.Broadcast();
}

void AABPlayerState::SetCurBullet(int32 Bullet)
{

	
	

	


	CurBullet += Bullet;


	OnPlayerStateChange.Broadcast();

	//UE_LOG(LogTemp, Warning, TEXT("Bullet Num: %d"), CurBullet);
	
}

void AABPlayerState::ReLoadBullet(int32 Bullet)
{
	CurBullet = Bullet;

	OnPlayerStateChange.Broadcast();
}

void AABPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
	auto GameInstance = Cast<UABGameInstance>(GetGameInstance());
	
	CurStatData = GameInstance->GetABCharacterData(NewCharacterLevel);
	
	CharLevel = NewCharacterLevel;



}
