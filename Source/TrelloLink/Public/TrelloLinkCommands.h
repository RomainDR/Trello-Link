// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "TrelloLinkStyle.h"

class FTrelloLinkCommands : public TCommands<FTrelloLinkCommands>
{
public:
	FTrelloLinkCommands()
		: TCommands<FTrelloLinkCommands>(TEXT("TrelloLink"), NSLOCTEXT("Contexts", "TrelloLink", "TrelloLink Plugin"),
		                                 NAME_None, FTrelloLinkStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> OpenPluginWindow;
};
