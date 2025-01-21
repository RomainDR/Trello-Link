#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "Widgets/SCompoundWidget.h"


class STrelloLinkSettings final : public SCompoundWidget
{
	
private:
	TSharedRef<SBox> CreateTab();
	FHttpModule* Http;
	const FString powerUpAPI = "4ca6d6fcc44e617fbd00097d1e96a201";
	const FString token = "ATTAf424bd43ee343f6386efe341a78a172efd90e0699c7cd495d4f4ef22b47fcc0d5688A3A3";
	const FString boardId = "678fa2b194b2c8ed7cb578eb";
	
public:
	SLATE_BEGIN_ARGS(STrelloLinkSettings)
	{
	}

	SLATE_END_ARGS()

private:
	void OnResponseAPI(TSharedPtr<IHttpRequest> HttpRequest, TSharedPtr<IHttpResponse> HttpResponse, bool bArg);
public:
	void Construct(const FArguments& InArgs);
};
