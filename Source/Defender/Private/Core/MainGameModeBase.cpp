// Copyright Epic Games, Inc. All Rights Reserved.


#include "Core/MainGameModeBase.h"
#include "Core/Multiplayer/MainGameSession.h"

AMainGameModeBase::AMainGameModeBase()
{
	GameSessionClass = AMainGameSession::StaticClass(); 
}
