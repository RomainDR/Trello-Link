﻿#include "TrelloLinkBoard.h"

#include "TrelloLink/Utils/TrelloLinkMacro.h"
#include "TrelloLink/Utils/TrelloUtils.h"
#include "Widgets/Layout/SWidgetSwitcher.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void STrelloLinkBoard::Construct(const FArguments& InArgs)
{
	LoadCredentials();
	ChildSlot
	[
		CreateTab()
	];
	SwitchPanel(static_cast<EStateWidget>(currentIndex));
}

void STrelloLinkBoard::LoadCredentials()
{	
	FString jsonFile;
	FFileHelper::LoadFileToString(jsonFile, *CREDENTIALS_PATH);
	if (jsonFile.IsEmpty())
		return;
	
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(jsonFile);
	TSharedPtr<FJsonValue> _result;
		
	if (FJsonSerializer::Deserialize(reader, _result))
	{
		powerUpToken	= _result->AsObject()->GetStringField(TEXT("powerUpToken"));
		token	= _result->AsObject()->GetStringField(TEXT("personalToken"));
		boardId	= _result->AsObject()->GetStringField(TEXT("boardId"));		
	}
	else
	{
		TrelloUtils::SendPopupError("Deserialize failed", "Error deserializing credentials json.");
	}
}

TSharedRef<SBox> STrelloLinkBoard::GetButtonsTabs()
{
	FSlateFontInfo font = FSlateFontInfo(RESOURCES_PATH + "Fonts/Roboto-Bold.ttf", SIZE_TITLE);

	return SNew(SBox)
		.MinDesiredHeight(50)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.Padding(20)

			[
				TrelloUtils::CreateButton("Create Card",
				                          FOnClicked::CreateLambda([&]
				                          {
					                          return SwitchPanel(EStateWidget::Create);
				                          }),
				                          FONT_BOLD(18), UPPER)
			]


			+ SHorizontalBox::Slot()
			.Padding(20)
			[
				TrelloUtils::CreateButton("Edit Card",
				                          FOnClicked::CreateLambda([&] { return SwitchPanel(EStateWidget::Edit); }),
				                          FONT_BOLD(18), UPPER)
			]
			+ SHorizontalBox::Slot()
			.Padding(20)
			[
				TrelloUtils::CreateButton("Delete Card",
				                          FOnClicked::CreateLambda([&] { return SwitchPanel(EStateWidget::Delete); }),
				                          FONT_BOLD(18), UPPER)
			]
			+ SHorizontalBox::Slot()
			.Padding(20)
			[
				TrelloUtils::CreateButton("Settings Card",
				                          FOnClicked::CreateLambda([&] { return SwitchPanel(EStateWidget::Settings); }),
				                          FONT_BOLD(18), UPPER)
			]
		];
}


TSharedRef<SWidget> STrelloLinkBoard::CreateTab()
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
			+ SWidgetSwitcher::Slot()
			[
				DeletePanel()
			]
		];
}

TSharedRef<SWidget> STrelloLinkBoard::CreatePanel()
{
	return TEXT_WIDGET("Create");
}

TSharedRef<SWidget> STrelloLinkBoard::EditPanel()
{
	return TEXT_WIDGET("Edit");
}

TSharedRef<SWidget> STrelloLinkBoard::DeletePanel()
{
	return TEXT_WIDGET("Delete");
}

FReply STrelloLinkBoard::SwitchPanel(const EStateWidget& _enum)
{
	const int _index = static_cast<int>(_enum);
	if (switcher->GetActiveWidgetIndex() == _index)	
		return FReply::Unhandled();
		
	if (_index > switcher->GetNumWidgets())
	{
		TrelloUtils::SendPopupError("Error", "Failed to open state at index " + FString::FromInt(_index));
		return FReply::Unhandled();
	}
	currentIndex = _index - 1;
	switcher->SetActiveWidgetIndex(_index);
	switch (_enum)
	{
	case EStateWidget::Create:
		OpenCreateFrame();
		break;
	case EStateWidget::Edit:
		OpenEditFrame();
		break;
	case EStateWidget::Delete:
		OpenDeleteFrame();
		break;
	default:
		return FReply::Unhandled();
	}
	return FReply::Handled();
}

void STrelloLinkBoard::OpenCreateFrame() const
{
	
}

void STrelloLinkBoard::OpenEditFrame() const
{
	
}

void STrelloLinkBoard::OpenDeleteFrame() const
{
	
}
