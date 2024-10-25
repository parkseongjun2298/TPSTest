// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootingGame.h"
#include "Engine/GameInstance.h"
#include"Engine/DataTable.h"
#include "ABGameInstance.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FABCharacterData:public FTableRowBase
{
	GENERATED_BODY()
public:
	FABCharacterData():Level(1),MaxHp(100.f),Attack(10.f){}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 MaxHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Attack;
};



UCLASS()
class SHOOTINGGAME_API UABGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UABGameInstance();
	virtual void Init()override;
	FABCharacterData* GetABCharacterData(int32 Level);
private:
	UPROPERTY()
	class UDataTable* ABCharacterTable;
	
};
