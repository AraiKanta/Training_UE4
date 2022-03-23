// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyTraining_ProjectGameMode.h"
#include "MyTraining_ProjectPawn.h"

AMyTraining_ProjectGameMode::AMyTraining_ProjectGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AMyTraining_ProjectPawn::StaticClass();
}

