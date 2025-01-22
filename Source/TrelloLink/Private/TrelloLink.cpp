// Copyright Epic Games, Inc. All Rights Reserved.

#include "TrelloLink.h"

#include "TrelloLinkStyle.h"
#include "TrelloLinkCommands.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "TrelloLink/Board/TrelloLinkBoard.h"
#include "TrelloLink/Edit/TrelloLinkSettings.h"
#include "TrelloLink/Utils/TrelloLinkMacro.h"

#pragma region Setup
static const FName TrelloLinkTabName("TrelloLink");
static const FName TrelloLinkSettingsTabName("TrelloLinkSettings");

#define LOCTEXT_NAMESPACE "FTrelloLinkModule"

void FTrelloLinkModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FTrelloLinkStyle::Initialize();
	FTrelloLinkStyle::ReloadTextures();

	FTrelloLinkCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FTrelloLinkModule::RegisterMenus));

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TrelloLinkTabName,
	                                                  FOnSpawnTab::CreateRaw(
		                                                  this, &FTrelloLinkModule::OnSpawnTrelloEditTab))
	                        .SetDisplayName(LOCTEXT("FTrelloLinkTabTitle", "Trello Link"))
	                        .SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TrelloLinkSettingsTabName,
	                                                  FOnSpawnTab::CreateRaw(
		                                                  this, &FTrelloLinkModule::OnSpawnTrelloSettingsTab))
	                        .SetDisplayName(LOCTEXT("FTrelloLinkSettingsTabTitle", "Trello Link Settings"))
	                        .SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FTrelloLinkModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FTrelloLinkStyle::Shutdown();

	FTrelloLinkCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TrelloLinkTabName);
}

TSharedRef<SDockTab> FTrelloLinkModule::OnSpawnTrelloEditTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(NomadTab)
		[
			SNew(STrelloLinkBoard)
		];
}

TSharedRef<SDockTab> FTrelloLinkModule::OnSpawnTrelloSettingsTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(NomadTab)
		[
			SNew(STrelloLinkSettings)
		];
}

void FTrelloLinkModule::OpenTrelloEdit()
{
	FGlobalTabmanager::Get()->TryInvokeTab(TrelloLinkTabName);
}

void FTrelloLinkModule::OpenTrelloSettings()
{
	FGlobalTabmanager::Get()->TryInvokeTab(TrelloLinkSettingsTabName);
}

void FTrelloLinkModule::CreateSubMenu(UToolMenu*& ExtendedMenu, const FString& _name, const FString& _tooltip)
{
	ExtendedMenu = ExtendedMenu->AddSubMenu(
		ExtendedMenu->MenuOwner,
		NAME_None,
		FName(_name),
		INVTEXT_OVERRIDE(_name),
		INVTEXT_OVERRIDE(_tooltip)
	);
}

UToolMenu* FTrelloLinkModule::GetToolMenu(const FName& _menuPath)
{
	UToolMenu* _menu = UToolMenus::Get()->ExtendMenu(_menuPath);
	if (!_menu)
		UE_LOG(LogTemp, Error, TEXT("Menu path: '%s' is null"), *_menuPath.ToString());
	return _menu;
}

FToolMenuSection& FTrelloLinkModule::AddAndGetMenuSection(UToolMenu* _menu, const FString& _sectionName)
{
	return _menu->AddSection(
		FName(_sectionName),
		INVTEXT_OVERRIDE(_sectionName)
	);
}

void FTrelloLinkModule::AddEntryToSection(FToolMenuSection& _section, const FString& _name, const FString& _tooltip,
                                          const FSlateIcon& _icon,
                                          const FUIAction& _callback)
{
	_section.AddMenuEntry(
		FName(_name),
		INVTEXT_OVERRIDE(_name),
		INVTEXT_OVERRIDE(_tooltip),
		_icon,
		_callback);
}

void FTrelloLinkModule::RegisterMenus()
{
	TArray<FName> ExtendedMenu = {
		"LevelEditor.MainMenu",
		"AssetEditor.WidgetBlueprintEditor.MainMenu",
		"AssetEditor.BlueprintEditor.MainMenu"
	};

	for (const FName& Menu : ExtendedMenu)
	{
		UToolMenu* _menu = GetToolMenu(Menu);

		CreateSubMenu(_menu, "Trello", "Open trello tools");

		FToolMenuSection& _section = AddAndGetMenuSection(_menu, "TrelloLink");

		AddEntryToSection(_section, "Trello Board", "Open the window to edit the board of trello",
		                  GET_ICON("TrelloLinkStyle", "TrelloLink.OpenPluginWindow"),
		CREATE_ACTION(FTrelloLinkModule, OpenTrelloEdit);

		AddEntryToSection(_section, "Trello Settings", "Open the settings of trello link module",
		                  GET_ICON("TrelloLinkStyle", "TrelloLink.OpenPluginWindow"),
		CREATE_ACTION(FTrelloLinkModule, OpenTrelloSettings);
	}
}
#pragma endregion Setup


#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FTrelloLinkModule, TrelloLink)
