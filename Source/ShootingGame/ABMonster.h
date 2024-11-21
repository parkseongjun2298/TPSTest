// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ABMonster.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);
UCLASS()
class SHOOTINGGAME_API AABMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	
	virtual void PostInitializeComponents()override;

	bool bAttackMode = false;
	int32 iZoomCount = 0;

	bool bReload = false;
	UPROPERTY(EditAnywhere, Category = "Bullet")
	TSubclassOf<class AABBullet> BulletList;


	UPROPERTY(VisibleAnywhere, Category = "Stat")
	class UABMonsterStatComponent* CharacterStat;

	UPROPERTY()
	class UABMonsterAnimInstance* ABAnim;

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)override;

	void Attack();

	bool bDead = false;

	void SetDead();
	/*void Reload();
	void NormalAttackStart();
	void NormalAttackEnd();*/
	UPROPERTY()
	class AABAIController* ABAIController;
	


	FOnAttackEndDelegate OnAttackEnd;
};
