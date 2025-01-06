// Copyright Epic Games, Inc. All Rights Reserved.

#include "TrelloLink.h"
#include "TrelloLinkStyle.h"
#include "TrelloLinkCommands.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "TrelloLink/UI/TrelloLinkDesign.h"

#pragma region Setup
static const FName TrelloLinkTabName("TrelloLink");

#define LOCTEXT_NAMESPACE "FTrelloLinkModule"

void FTrelloLinkModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FTrelloLinkStyle::Initialize();
	FTrelloLinkStyle::ReloadTextures();

	FTrelloLinkCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(

		FTrelloLinkCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FTrelloLinkModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FTrelloLinkModule::RegisterMenus));

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TrelloLinkTabName,
	                                                  FOnSpawnTab::CreateRaw(
		                                                  this, &FTrelloLinkModule::OnSpawnPluginTab))
	                        .SetDisplayName(LOCTEXT("FTrelloLinkTabTitle", "Trello Link"))
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

TSharedRef<SDockTab> FTrelloLinkModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			//SNew(SBox)
			//.HAlign(HAlign_Center)
			//.VAlign(VAlign_Center)
			//[
			SNew(STrelloLinkDesign)
			//]
		];
}

void FTrelloLinkModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(TrelloLinkTabName);
}

void FTrelloLinkModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FTrelloLinkCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(
					FToolMenuEntry::InitToolBarButton(FTrelloLinkCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}
#pragma endregion Setup


#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FTrelloLinkModule, TrelloLink)
