// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPlayerController.h"
#include"ABHUDWidget.h"
#include"ABPlayerState.h"
AABPlayerController::AABPlayerController()
{
	static ConstructorHelpers::FClassFinder<UABHUDWidget>UI_HUD_C(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UserWidget.UserWidget_C'"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}
}

void AABPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AABPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

UABHUDWidget* AABPlayerController::GetHUDWidget() const
{
	return HUDWidget;
}



void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	HUDWidget = CreateWidget<UABHUDWidget>(this, HUDWidgetClass);
	HUDWidget->AddToViewport();

	 PlayerState = Cast<AABPlayerState>(PlayerState); //여기서 안댐 AABPlayerController의 PlayerState 이녀석이 속이 비어있음 이걸 값잇게해야함
	 if (PlayerState != nullptr)
	 {
		 HUDWidget->BindPlayerState(PlayerState);

		 PlayerState->OnPlayerStateChange.Broadcast();

	 }

}
