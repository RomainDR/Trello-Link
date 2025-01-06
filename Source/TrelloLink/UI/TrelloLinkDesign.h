#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

enum class EStateWidget
{
	Create, Edit, /*Delete,*/ Settings
};

class STrelloLinkDesign final : public SCompoundWidget
{
private:
	TSharedPtr<SWidgetSwitcher> switcher;
	int currentIndex = static_cast<int>(EStateWidget::Create);

public:
	SLATE_BEGIN_ARGS(STrelloLinkDesign)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	TSharedRef<SBox> GetButtonsTabs();
	TSharedRef<SWidget> CreateTab();
	TSharedRef<SWidget> EditPanel();
	TSharedRef<SWidget> CreatePanel();

	FReply SwitchPanel(const EStateWidget& _enum);
	FReply SwitchToSettings();
	FReply SwitchToCreate();
	FReply SwitchToEdit();
	FReply OpenSettings();
	FReply OpenCreateFrame();
	FReply OpenEditFrame();
	void SendPopup(const FString& _text, const FString& _subText = FString()) const;
};
