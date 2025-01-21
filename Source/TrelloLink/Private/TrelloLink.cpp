// Copyright Epic Games, Inc. All Rights Reserved.

#include "TrelloLink.h"

#include "LevelEditor.h"
#include "SourceCodeNavigation.h"
#include "TrelloLinkStyle.h"
#include "TrelloLinkCommands.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "TrelloLink/Board/TrelloLinkBoard.h"
#include "TrelloLink/Edit/TrelloLinkSettings.h"

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

	/*PluginCommands->MapAction(
		FTrelloLinkCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FTrelloLinkModule::OpenTrelloEdit),
		FCanExecuteAction());*/

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
			//SNew(SBox)
			//.HAlign(HAlign_Center)
			//.VAlign(VAlign_Center)
			//[
			SNew(STrelloLinkBoard)
			//]
		];
}

TSharedRef<SDockTab> FTrelloLinkModule::OnSpawnTrelloSettingsTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(NomadTab)
		[
			//SNew(SBox)
			//.HAlign(HAlign_Center)
			//.VAlign(VAlign_Center)
			//[
			SNew(STrelloLinkSettings)
			//]
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

void FTrelloLinkModule::RegisterMenus()
{
	//
	// // Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	// FToolMenuOwnerScoped OwnerScoped(this);
	//
	//
	// UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu");
	// {
	// 	/*FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
	// 	Section.AddMenuEntryWithCommandList(FTrelloLinkCommands::Get().OpenPluginWindow, PluginCommands);*/
	//}

	/// Get Editor's main menu to extend it
	UToolMenu* MainMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu");
	
	/// Add the SubMenu "Editor"
	UToolMenu* EditorMenu = MainMenu->AddSubMenu(
		MainMenu->MenuOwner,
		NAME_None,
		FName("Trello"),
		INVTEXT("Trello"),
		INVTEXT("Open Trello tool")
	);

	/// Add the section "EDITOR TOOL"
	FToolMenuSection& Section = EditorMenu->AddSection(
		"TrelloLink",
		INVTEXT("TrelloLink")
	);

	/// Add the command "Trello"
	Section.AddMenuEntry(
		"Trello Editor",
		INVTEXT("Trello"),
		INVTEXT("Open the trello editor, to edit card"),
		FSlateIcon(FName("TrelloLinkStyle"), "TrelloLink.OpenPluginWindow"),
		FUIAction(FExecuteAction::CreateLambda([&] { OpenTrelloEdit(); } ))
	);
	
	Section.AddMenuEntry(
		"Trello Settings",
		INVTEXT("Trello Settings"),
		INVTEXT("Change the settings of board trello"),
		FSlateIcon(FName("TrelloLinkStyle"), "TrelloLink.OpenPluginWindow"),
		FUIAction(FExecuteAction::CreateLambda([&] { OpenTrelloSettings(); } ))
	);
	
}
#pragma endregion Setup


#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FTrelloLinkModule, TrelloLink)
