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
	auto Pawn = TryGetPawnOwner();

	if (!::IsValid(Pawn))return;


	if (!isDead)
	{
		auto Monster = Cast<AABMonster>(Pawn);
		if (::IsValid(Monster))
		{
			AttackMode = Monster->bAttackMode;
			Speed = Monster->GetVelocity().Size();

			isReload = Monster->bReload;

			isDead= Monster->bDead;
		}
	}
}

void UABMonsterAnimInstance::AnimNotify_FireBullet()
{
	OnFireBulletDelegate.Broadcast();
}

void UABMonsterAnimInstance::AnimNotify_Reload()
{
	OnReloadDelegate.Broadcast();
}

void UABMonsterAnimInstance::AnimNotify_Dead()
{
	OnDeadDelegate.Broadcast();
}

void UABMonsterAnimInstance::AnimNotify_AttackEnd()
{
	OnAttackEndDelegate.Broadcast();
}
