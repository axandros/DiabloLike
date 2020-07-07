// Copyright Epic Games, Inc. All Rights Reserved.

#include "DiabloLikeGameMode.h"
#include "DiabloLikePlayerController.h"
#include "DiabloLikeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADiabloLikeGameMode::ADiabloLikeGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ADiabloLikePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}