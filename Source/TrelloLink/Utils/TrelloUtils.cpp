#include "TrelloUtils.h"

#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

void TrelloUtils::SendPopupWarning(const FString& _title, const FString& _message, EAppMsgType::Type _type)
{
	FMessageDialog::Open(EAppMsgCategory::Warning, _type, FText::FromString(_message), FText::FromString(_title));
}

void TrelloUtils::SendPopupInformation(const FString& _title, const FString& _message, EAppMsgType::Type _type)
{
	FMessageDialog::Open(EAppMsgCategory::Info, _type, FText::FromString(_message), FText::FromString(_title));
}

void TrelloUtils::SendPopupError(const FString& _title, const FString& _message, EAppMsgType::Type _type)
{
	FMessageDialog::Open(EAppMsgCategory::Error, _type, FText::FromString(_message), FText::FromString(_title));
}

void TrelloUtils::SendPopupSuccess(const FString& _title, const FString& _message, EAppMsgType::Type _type)
{
	FMessageDialog::Open(EAppMsgCategory::Success, _type, FText::FromString(_message), FText::FromString(_title));
}

void TrelloUtils::SendPopupEngine(const FString& _text, const FString& _subText)
{
	FNotificationInfo Info(FText::FromString(_text));
	Info.SubText = FText::FromString(_subText);
	FSlateNotificationManager::Get().AddNotification(Info);
}

TSharedRef<SButton> TrelloUtils::CreateButton(const FString& _text, const FOnClicked& _callback,
                                              const FSlateFontInfo& _font, const ETextTransformPolicy& _transformPolicy)
{
	return BUTTON_WIDGET(_text, _callback, HCenter, VCenter, _transformPolicy, _font);
}
