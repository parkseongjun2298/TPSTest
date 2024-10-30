// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootingGame.h"
#include "Components/ActorComponent.h"
#include "ABPlayerStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTINGGAME_API UABPlayerStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UABPlayerStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent()override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	struct FABCharacterData* CurStatData = nullptr;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess=true))
	float CurHp;
	UPROPERTY(EditInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 MaxBullet;
	UPROPERTY(Transient, VisibleInstanceOnly,Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 CurBullet;

public:
	void SetNewLevel(int32 NewLevel);
	int32 GetMaxBullet();
	int32 GetCurBullet();
	void SetMaxBullet(int32 Bullet);
	void SetCurBullet(int32 Bullet);
};
