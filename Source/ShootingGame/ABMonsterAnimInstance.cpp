// Fill out your copyright notice in the Description page of Project Settings.


#include "ABMonsterAnimInstance.h"
#include"ABMonster.h"
UABMonsterAnimInstance::UABMonsterAnimInstance()
{
	AttackMode = false;
	Speed = 0.f;
}

void UABMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UABMonsterAnimInstance::AnimNotify_FireBullet()
{
	OnFireBulletDelegate.Broadcast();
}

void UABMonsterAnimInstance::AnimNotify_Reload()
{
	OnReloadDelegate.Broadcast();
}
