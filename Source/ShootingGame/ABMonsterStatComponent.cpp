// Fill out your copyright notice in the Description page of Project Settings.


#include "ABMonsterStatComponent.h"
#include"ABGameInstance.h"
// Sets default values for this component's properties
UABMonsterStatComponent::UABMonsterStatComponent()
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
void UABMonsterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UABMonsterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
}


// Called every frame
void UABMonsterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UABMonsterStatComponent::SetNewLevel(int32 NewLevel)
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

		UE_LOG(LogTemp, Warning, TEXT("MonsterLevel(%d)data doesn`t exist"), NewLevel);
	}
}

