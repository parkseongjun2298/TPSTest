// Fill out your copyright notice in the Description page of Project Settings.


#include "ABHUDWidget.h"
#include"Components/TextBlock.h"
#include"ABPlayerState.h"
#include"ABPlayerStatComponent.h"
#include"Components/ProgressBar.h"
void UABHUDWidget::BindCharacterStat(UABPlayerStatComponent* CharacterStat)
{
	CurCharacterStat = CharacterStat;

}

void UABHUDWidget::BindPlayerState(AABPlayerState* PlayerState)
{
	CurPlayerState = PlayerState;

	if (IsValid(PlayerState))
	{
		CurPlayerState = PlayerState;
		PlayerState->OnPlayerStateChange.AddUObject(this, &UABHUDWidget::UpdatePlayerState);

	

	}


	UE_LOG(LogTemp, Warning, TEXT("Novalid"));
	
}

void UABHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//PlayerName = Cast<UTextBlock>(GetWidgetFromName(TEXT("")));

	CurBullet= Cast<UTextBlock>(GetWidgetFromName(TEXT("CurBulletNum")));
	MaxBullet = Cast<UTextBlock>(GetWidgetFromName(TEXT("MaxBulletNum")));

	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP_Bar")));
	EXPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("EXP_Bar")));
}

void UABHUDWidget::UpdateCharacterStat()
{
}

void UABHUDWidget::UpdatePlayerState()
{
	CurBullet->SetText(FText::FromString(FString::FromInt(CurPlayerState->GetCurBullet())));
	MaxBullet->SetText(FText::FromString(FString::FromInt(CurPlayerState->GetMaxBullet())));

	
	UE_LOG(LogTemp, Warning, TEXT("Update"));

	

}
