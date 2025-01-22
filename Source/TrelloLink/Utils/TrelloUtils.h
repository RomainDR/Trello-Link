#pragma once
#include "TrelloLinkMacro.h"

class TrelloUtils
{
public:
	static void SendPopupWarning(const FString& _title, const FString& _message,
	                             EAppMsgType::Type _type = EAppMsgType::Type::Ok);
	static void SendPopupInformation(const FString& _title, const FString& _message,
	                                 EAppMsgType::Type _type = EAppMsgType::Type::Ok);
	static void SendPopupError(const FString& _title, const FString& _message,
	                           EAppMsgType::Type _type = EAppMsgType::Type::Ok);
	static void SendPopupSuccess(const FString& _title, const FString& _message,
	                             EAppMsgType::Type _type = EAppMsgType::Type::Ok);
	static void SendPopupEngine(const FString& _text, const FString& _subText);

	static TSharedRef<STextBlock> CreateText(const FString& _text);
	static TSharedRef<SButton> CreateButton(const FString& _text, const FOnClicked& _callback,
	                                        const FSlateFontInfo& _font = FONT_BOLD(18),
	                                        const ETextTransformPolicy& _transformPolicy = ETextTransformPolicy::None);
};
