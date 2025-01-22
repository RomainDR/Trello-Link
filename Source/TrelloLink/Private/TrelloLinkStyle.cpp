// Copyright Epic Games, Inc. All Rights Reserved.

#include "TrelloLinkStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

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
	{
		FSlateStyleRegistry::RegisterSlateStyle(*SlateStyleSet);
	}
}

void FTrelloLinkStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();

	for (const TSharedRef<FSlateStyleSet>& Style : styles)
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*Style);
	}
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
	TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet("TrelloLinkStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("TrelloLink")->GetBaseDir() / TEXT("Resources"));
	Style->Set("TrelloLink.OpenPluginWindow",
	           new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), FVector2D(20.0f, 20.0f)));
	return Style;
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
