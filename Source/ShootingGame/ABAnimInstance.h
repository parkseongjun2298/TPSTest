// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootingGame.h"
#include "Animation/AnimInstance.h"
#include "ABAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnFireBulletDelegate);
DECLARE_MULTICAST_DELEGATE(FOnReloadDelegate);
/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API UABAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UABAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character", Meta = (AllowPrivateAccess = true))
	bool AttackMode;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character", Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character", Meta = (AllowPrivateAccess = true))
	bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character", Meta = (AllowPrivateAccess = true))
	bool isReload;


private:
	UFUNCTION()
	void AnimNotify_FireBullet();

	UFUNCTION()
	void AnimNotify_Reload();
public:
	FOnFireBulletDelegate OnFireBulletDelegate;
	FOnReloadDelegate OnReloadDelegate;
};
