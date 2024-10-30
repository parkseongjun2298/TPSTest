// Fill out your copyright notice in the Description page of Project Settings.


#include "ABHUDWidget.h"
#include"Components/TextBlock.h"
#include"ABPlayerState.h"

void UABHUDWidget::BindCharacterStat()
{
}

void UABHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//PlayerName = Cast<UTextBlock>(GetWidgetFromName(TEXT("")));

	CurBullet= Cast<UTextBlock>(GetWidgetFromName(TEXT("CurBulletNum")));
	MaxBullet = Cast<UTextBlock>(GetWidgetFromName(TEXT("MaxBulletNum")));

}

void UABHUDWidget::UpdateCharacterStat()
{
}

void UABHUDWidget::UpdatePlayerState()
{
	//CurBullet->SetText(FText::FromString(FString::FromInt());
}
