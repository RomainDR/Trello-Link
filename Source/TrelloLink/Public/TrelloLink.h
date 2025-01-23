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
	/**
	 * Register all menus custom for plugin
	 */
	void RegisterMenus();
	/**
	 * Create sub menu in ToolMenu. ToolMenu can be get with GetToolMenu
	 * @param ExtendedMenu ToolMenu is section where menu will be added
	 * @param _name Name showed
	 * @param _tooltip tooltip when mouse hovered
	 */
	void CreateSubMenu(UToolMenu*& ExtendedMenu, const FString& _name, const FString& _tooltip);
	/**
	 * Add an entry to section
	 * @param _section Section of toolMenui
	 * @param _name Name of entry
	 * @param _tooltip Tooltip of entry
	 * @param _icon Icon of entry (can be get with macro CREATE_ICON)
	 * @param _callback Callback of entry (can be get with macro CREATE_ACTION)
	 */
	void AddEntryToSection(FToolMenuSection& _section, const FString& _name, const FString& _tooltip,
	                       const FSlateIcon& _icon, const FUIAction& _callback);
	/**
	 * Get the toolMenu
	 * @param _menuPath The path of menu in engine. Can be showed with 'ToolMenus.Edit' in console. Like this 'LevelEditor.MainMenu'
	 * @return A ToolMenu pointer of path. Can be null.
	 */
	UToolMenu* GetToolMenu(const FName& _menuPath);
	/**
	 * Add and Get the section created in ToolMenu
	 * @param _menu ToolMenu when created
	 * @param _sectionName The section name
	 * @return A FToolMenuSection reference to use
	 */
	FToolMenuSection& AddAndGetMenuSection(UToolMenu* _menu, const FString& _sectionName);
	void OnTabRelocated();
	/**
	 * Create and spawn a new window slate
	 * @param SpawnTabArgs 
	 * @return 
	 */
	TSharedRef<SDockTab> OnSpawnTrelloEditTab(const FSpawnTabArgs& SpawnTabArgs);
	/**
	 * Create and spawn a new window slate
	 * @param SpawnTabArgs 
	 * @return 
	 */
	TSharedRef<SDockTab> OnSpawnTrelloSettingsTab(const FSpawnTabArgs& SpawnTabArgs);
#pragma endregion Unreal Setup
};
