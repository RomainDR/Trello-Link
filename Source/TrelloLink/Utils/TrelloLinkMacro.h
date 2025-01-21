#pragma once

#include "Interfaces/IPluginManager.h"

//----- [PATH] -----
#define RESOURCES_PATH IPluginManager::Get().FindPlugin("TrelloLink")->GetBaseDir() + "/Resources"
//----- [PATH] -----

//----- [FONT] -----
#define FONT_BOLD(size) FSlateFontInfo(RESOURCES_PATH + "/Fonts/Roboto-Bold.ttf", size)
//----- [FONT] -----

//----- [TEXT] -----
#define SIZE_TITLE 18
#define SIZE_TEXT 14
#define TEXT_WIDGET(_text) SNew(STextBlock).Text(FText::FromString(_text))

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
//----- [ALIGNMENT] -----