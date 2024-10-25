// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameInstance.h"

UABGameInstance::UABGameInstance()
{
	FString CharacterDataPath = TEXT("/Script/Engine.DataTable'/Game/Data/ABCharacterDataTable.ABCharacterDataTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable>DT_ABCharacter(*CharacterDataPath);
	
	ABCharacterTable = DT_ABCharacter.Object;


	
}

void UABGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("Att of Character :%d"), GetABCharacterData(1)->Attack);


}

FABCharacterData* UABGameInstance::GetABCharacterData(int32 Level)
{
	return ABCharacterTable->FindRow<FABCharacterData>(*FString::FromInt(Level),TEXT(""));
}
