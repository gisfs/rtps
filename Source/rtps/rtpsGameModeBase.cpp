// Copyright Epic Games, Inc. All Rights Reserved.


#include "rtpsGameModeBase.h"
#include "SandboxPawn.h"
#include "SandboxPlayerController.h"
ArtpsGameModeBase::ArtpsGameModeBase()
{
	DefaultPawnClass = ASandboxPawn::StaticClass();
	PlayerControllerClass = ASandboxPlayerController::StaticClass();

}