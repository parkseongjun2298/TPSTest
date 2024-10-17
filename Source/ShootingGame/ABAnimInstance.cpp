// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAnimInstance.h"
#include"ABCharacter.h"
UABAnimInstance::UABAnimInstance()
{
	AttackMode = false;
	Speed = 0.f;

}

void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto Pawn = TryGetPawnOwner();

	auto Player = Cast<AABCharacter>(Pawn);
	if (::IsValid(Player))
	{
		AttackMode = Player->bAttackMode;
		Speed = Player->GetVelocity().Size();
	}

}