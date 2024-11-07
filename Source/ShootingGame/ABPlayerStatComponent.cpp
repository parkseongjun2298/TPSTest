// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPlayerStatComponent.h"
#include"ABGameInstance.h"
// Sets default values for this component's properties
UABPlayerStatComponent::UABPlayerStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	// ...
	Level = 1;
	MaxBullet = 1;
	CurBullet = 1;

}


// Called when the game starts
void UABPlayerStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UABPlayerStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
}


// Called every frame
void UABPlayerStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UABPlayerStatComponent::SetNewLevel(int32 NewLevel)
{
	auto GameInstnace = Cast<UABGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	CurStatData = GameInstnace->GetABCharacterData(NewLevel);
	if (nullptr != CurStatData)
	{
		Level = NewLevel;
		CurHp = CurStatData->MaxHp;
		MaxBullet = CurStatData->MaxBullet;
		CurBullet = CurStatData->CurBullet;
	}
	else

	{

		UE_LOG(LogTemp,Warning, TEXT("Level(%d)data doesn`t exist"), NewLevel);
	}
}

//int32 UABPlayerStatComponent::GetMaxBullet()
//{
//	return MaxBullet;
//
//}
//
//int32 UABPlayerStatComponent::GetCurBullet()
//{
//	return CurBullet;
//
//}
//
//void UABPlayerStatComponent::SetMaxBullet(int32 Bullet)
//{
//	MaxBullet = Bullet;
//}
//
//void UABPlayerStatComponent::SetCurBullet(int32 Bullet)
//{
//	CurBullet += Bullet;
//}
