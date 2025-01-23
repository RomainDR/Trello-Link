#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "Widgets/SCompoundWidget.h"


class STrelloLinkSettings final : public SCompoundWidget
{
private:
	TSharedPtr<SEditableTextBox> powerUpField;
	TSharedPtr<SEditableTextBox> tokenField;
	TSharedPtr<SEditableTextBox> idBoardField;
	FHttpModule* Http = nullptr;

public:
	SLATE_BEGIN_ARGS(STrelloLinkSettings)
		{
		}

	SLATE_END_ARGS()
private:
	void LoadCredentials();
	void OnResponseAPI(TSharedPtr<IHttpRequest> HttpRequest, TSharedPtr<IHttpResponse> HttpResponse, bool bArg);
	FReply TestConnection() const;
	FReply SaveCredentials() const;
	TSharedRef<SVerticalBox> CreateSection(TSharedPtr<SEditableTextBox>& _assign, const FString& _title,
	                                       const FString& _description,
	                                       const FString& _placeholder) const;
	TSharedRef<SBox> CreateTab();

public:
	void Construct(const FArguments& InArgs);
};
