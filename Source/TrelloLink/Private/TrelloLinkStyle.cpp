// Copyright Epic Games, Inc. All Rights Reserved.

#include "TrelloLinkStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"
#include "TrelloLink/Utils/TrelloLinkMacro.h"

#define RootToContentDir Style->RootToContentDir

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedPtr<FSlateStyleSet> FTrelloLinkStyle::StyleInstance = nullptr;
TArray<TSharedRef<FSlateStyleSet>> FTrelloLinkStyle::styles = {};

void FTrelloLinkStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
	CreateIcons();
	for (const TSharedRef<FSlateStyleSet>& SlateStyleSet : styles)	
		FSlateStyleRegistry::RegisterSlateStyle(*SlateStyleSet);
	
}

void FTrelloLinkStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();

	for (const TSharedRef<FSlateStyleSet>& Style : styles)	
		FSlateStyleRegistry::UnRegisterSlateStyle(*Style);
}

FName FTrelloLinkStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("TrelloLinkStyle"));
	return StyleSetName;
}

void FTrelloLinkStyle::CreateIcons()
{
	//TODO create icons
}

TSharedRef<FSlateStyleSet> FTrelloLinkStyle::Create()
{
	CREATE_ICON("TrelloLinkStyle", "TrelloLink.OpenPluginWindow", "PlaceholderButtonIcon", Icon20x20);
}

void FTrelloLinkStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FTrelloLinkStyle::Get()
{
	return *StyleInstance;
}
