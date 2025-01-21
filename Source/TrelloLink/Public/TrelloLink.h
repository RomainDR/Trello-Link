// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FTrelloLinkModule : public IModuleInterface
{
#pragma region Unreal Setup
	
	TSharedPtr<FUICommandList> PluginCommands;

public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	void OpenTrelloEdit();
	void OpenTrelloSettings();

private:
	void RegisterMenus();
/*	void AddMenu(FMenuBarBuilder& MenuBarBuilder);
	void FillMenu(FMenuBuilder& MenuBuilder);*/
	TSharedRef<SDockTab> OnSpawnTrelloEditTab(const class FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<SDockTab> OnSpawnTrelloSettingsTab(const FSpawnTabArgs& SpawnTabArgs);
#pragma endregion Unreal Setup
};
