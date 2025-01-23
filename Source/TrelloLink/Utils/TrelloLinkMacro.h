#pragma once

#include "Interfaces/IPluginManager.h"

//----- [PADDING] -----//
#define PADDING_8(size) size * 8
#define PADDING_4(size) size * 4
//----- [PADDING] -----//

//----- [PATH] -----
#define RESOURCES_PATH IPluginManager::Get().FindPlugin("TrelloLink")->GetBaseDir() + "/Resources"
#define CREDENTIALS_PATH FPaths::Combine(FPaths::ProjectConfigDir(),"credentials_trello.json")
//----- [PATH] -----

//----- [FONT] -----
#define FONT_BOLD(size) FSlateFontInfo(RESOURCES_PATH + "/Fonts/Roboto-Bold.ttf", size)
#define FONT_ITALIC(size) FSlateFontInfo(RESOURCES_PATH + "/Fonts/Roboto-Italic.ttf", size)
#define FONT_NORMAL(size) FSlateFontInfo(RESOURCES_PATH + "/Fonts/Roboto-Medium.ttf", size)
//----- [FONT] -----

//----- [TEXT] -----
#define SIZE_TITLE 18
#define SIZE_TEXT 14
#define TEXT_WIDGET(_text) SNew(STextBlock).Text(FText::FromString(_text))
#define FTEXT(str) FText::FromString(str)
#define FORMAT(fstring, ...) FString::Format(*fstring, {__VA_ARGS__})
//----- [TEXT] -----

//----- [BUTTON] -----
#define BUTTON_WIDGET(_text, _callback, _HAlign, _VAlign, _transformPolicy, _font) \
SNew(SButton) \
.HAlign(_HAlign) \
.VAlign(_VAlign) \
.OnClicked(_callback) \
[ \
TEXT_WIDGET(_text) \
.TransformPolicy(_transformPolicy) \
.Font(_font) \
];
//----- [BUTTON] -----

//----- [TRANSFORM POLICY] -----
#define LOWER ETextTransformPolicy::ToLower
#define UPPER ETextTransformPolicy::ToUpper
#define NONE ETextTransformPolicy::None
//----- [TRANSFORM POLICY] -----

//----- [ALIGNMENT] -----
#define HCenter HAlign_Center
#define HLeft HAlign_Left
#define HRight HAlign_Right

#define VCenter VAlign_Center
#define VLeft VAlign_Left
#define VRight VAlign_Right
#define VTop VAlign_Top
//----- [ALIGNMENT] -----


//----[OVERRIDE] -----//
#define INVTEXT_OVERRIDE(str) FText::AsCultureInvariant(str)
#define GET_ICON(nameStyle, nameIcon) FSlateIcon(FName(nameStyle), nameIcon)
#define CREATE_ACTION(clazz, method) FUIAction(FExecuteAction::CreateRaw(this, &clazz::method)));
//----[OVERRIDE] -----//
