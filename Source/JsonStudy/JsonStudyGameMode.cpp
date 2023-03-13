// Copyright Epic Games, Inc. All Rights Reserved.

#include "JsonStudyGameMode.h"
#include "JsonStudyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AJsonStudyGameMode::AJsonStudyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
