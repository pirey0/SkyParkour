// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SkyParkourGameMode.h"
#include "SkyParkourHUD.h"
#include "SkyParkourCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASkyParkourGameMode::ASkyParkourGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASkyParkourHUD::StaticClass();
}
