#include "TrelloLinkDesign.h"
#include "../../TrelloLink/TrelloLinkMacro.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Layout/SWidgetSwitcher.h"
#include "Widgets/Notifications/SNotificationList.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void STrelloLinkDesign::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		CreateTab()
	];
	switcher->SetActiveWidgetIndex(currentIndex);
}

TSharedRef<SBox> STrelloLinkDesign::GetButtonsTabs()
{
	FSlateFontInfo font = FSlateFontInfo(RESOURCES_PATH + "Fonts/Roboto-Bold.ttf", SIZE_TITLE);

	return SNew(SBox)
		.MinDesiredHeight(50)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.Padding(20)
			[
				SNew(SButton)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.OnClicked_Raw(this, &STrelloLinkDesign::SwitchToCreate)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Create card"))
					.Font(font)
					.TransformPolicy(ETextTransformPolicy::ToUpper)
				]
			]
			+ SHorizontalBox::Slot()
			.Padding(20)
			[
				SNew(SButton)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.OnClicked_Raw(this, &STrelloLinkDesign::SwitchToEdit)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Edit card"))
					.Font(font)
					.TransformPolicy(ETextTransformPolicy::ToUpper)
				]
			]
			+ SHorizontalBox::Slot()
			.Padding(20)
			[
				SNew(SButton)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.OnClicked_Raw(this, &STrelloLinkDesign::SwitchToSettings)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Settings"))
					.Font(font)
					.TransformPolicy(ETextTransformPolicy::ToUpper)
				]
			]
		];
}

TSharedRef<SWidget> STrelloLinkDesign::CreatePanel()
{
	return SNew(STextBlock)
		.Text(FText::FromString("Create"));
}

TSharedRef<SWidget> STrelloLinkDesign::CreateTab()
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			GetButtonsTabs()
		]
		+ SVerticalBox::Slot()
		.Padding(16.f)
		[
			SAssignNew(switcher, SWidgetSwitcher)
			+ SWidgetSwitcher::Slot()
			[
				CreatePanel()
			]
			+ SWidgetSwitcher::Slot()
			[
				EditPanel()
			]
		];
}

TSharedRef<SWidget> STrelloLinkDesign::EditPanel()
{
	return SNew(STextBlock)
		.Text(FText::FromString("Edit"));
}

FReply STrelloLinkDesign::SwitchPanel(const EStateWidget& _enum)
{
	const int _index = static_cast<int>(_enum);
	if (switcher->GetActiveWidgetIndex() == _index)
		return FReply::Unhandled();

	if (_index > switcher->GetAllChildren()->Num())
	{
		SendPopup("Failed to open state at index " + FString::FromInt(_index), "test");
		return FReply::Unhandled();
	}
	currentIndex = _index;
	
	switcher->SetActiveWidgetIndex(_index);
	switch (_enum)
	{
	case EStateWidget::Create:
		return OpenCreateFrame();
	case EStateWidget::Edit:
		return OpenEditFrame();
		break;
	/*case EStateWidget::Delete:
		break;*/
	case EStateWidget::Settings:
		return OpenSettings();
	default:
		return FReply::Unhandled();
	}
	return FReply::Handled();
}

FReply STrelloLinkDesign::SwitchToSettings()
{
	return SwitchPanel(EStateWidget::Settings);
}

FReply STrelloLinkDesign::SwitchToCreate()
{
	return SwitchPanel(EStateWidget::Create);
}

FReply STrelloLinkDesign::SwitchToEdit()
{
	return SwitchPanel(EStateWidget::Edit);
}

FReply STrelloLinkDesign::OpenEditFrame()
{
	GLog->Log("Open edit");
	SendPopup("Open edit");
	return FReply::Handled();
}

FReply STrelloLinkDesign::OpenSettings()
{
	GLog->Log("Open settings");
	SendPopup("Open settings");
	return FReply::Handled();
}

FReply STrelloLinkDesign::OpenCreateFrame()
{
	GLog->Log("Open frame");
	SendPopup("Open create frame");
	return FReply::Handled();
}

void STrelloLinkDesign::SendPopup(const FString& _text, const FString& _subText) const
{
	FNotificationInfo Info(FText::FromString(_text));
	Info.SubText = FText::FromString(_subText);
	FSlateNotificationManager::Get().AddNotification(Info);
}
