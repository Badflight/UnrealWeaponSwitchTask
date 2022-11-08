// Copyright Epic Games, Inc. All Rights Reserved.

#include "UNREALTASK6GameMode.h"
#include "UNREALTASK6Character.h"
#include "UObject/ConstructorHelpers.h"

AUNREALTASK6GameMode::AUNREALTASK6GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
