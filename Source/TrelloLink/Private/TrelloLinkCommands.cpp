// Copyright Epic Games, Inc. All Rights Reserved.

#include "TrelloLinkCommands.h"

#define LOCTEXT_NAMESPACE "FTrelloLinkModule"

void FTrelloLinkCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "TrelloLink", "Open trello window", EUserInterfaceActionType::Button,
	           FInputChord());
}

#undef LOCTEXT_NAMESPACE
