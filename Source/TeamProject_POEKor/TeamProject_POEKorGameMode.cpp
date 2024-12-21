// Copyright Epic Games, Inc. All Rights Reserved.

#include "TeamProject_POEKorGameMode.h"
#include "TeamProject_POEKorCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATeamProject_POEKorGameMode::ATeamProject_POEKorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
