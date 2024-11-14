// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ABMonsterAnimInstance.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnFireBulletDelegate);
DECLARE_MULTICAST_DELEGATE(FOnReloadDelegate);
DECLARE_MULTICAST_DELEGATE(FOnDeadDelegate);

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API UABMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	UABMonsterAnimInstance();
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character", Meta = (AllowPrivateAccess = true))
	bool isDead;
private:
	UFUNCTION()
	void AnimNotify_FireBullet();

	UFUNCTION()
	void AnimNotify_Reload();

	UFUNCTION()
	void AnimNotify_Dead();
public:
	FOnFireBulletDelegate OnFireBulletDelegate;
	FOnReloadDelegate OnReloadDelegate;
	FOnDeadDelegate OnDeadDelegate;
	
};
