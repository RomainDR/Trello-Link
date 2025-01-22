#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

enum class EStateWidget
{
	Create, Edit, Delete, Settings
};

class STrelloLinkBoard final : public SCompoundWidget
{
private:
	TSharedPtr<SWidgetSwitcher> switcher;
	int currentIndex = static_cast<int>(EStateWidget::Create);

private:
	TSharedRef<SBox> GetButtonsTabs();
	TSharedRef<SWidget> CreateTab();
	TSharedRef<SWidget> CreatePanel();
	TSharedRef<SWidget> EditPanel();
	TSharedRef<SWidget> DeletePanel();

	FReply SwitchPanel(const EStateWidget& _enum);
	void OpenCreateFrame() const;
	void OpenEditFrame() const;
	void OpenDeleteFrame() const;

public:
	SLATE_BEGIN_ARGS(STrelloLinkBoard)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
};
