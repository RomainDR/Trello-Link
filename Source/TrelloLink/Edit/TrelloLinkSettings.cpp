#include "TrelloLinkSettings.h"

#include "JsonObjectConverter.h"
#include "Components/BorderSlot.h"
#include "Components/SizeBox.h"
#include "Interfaces/IHttpResponse.h"
#include "Interfaces/IPluginManager.h"
#include "JsonUtils/JsonPointer.h"
#include "TrelloLink/Utils/TrelloLinkMacro.h"
#include "Widgets/SCanvas.h"
#include "Widgets/Layout/SScaleBox.h"
#include "Widgets/Layout/SUniformGridPanel.h"


void STrelloLinkSettings::OnResponseAPI(TSharedPtr<IHttpRequest> HttpRequest, TSharedPtr<IHttpResponse> HttpResponse,
                                        bool bArg)
{
	TSharedPtr<FJsonObject> JsonObject; //Crée un json object
	if (HttpResponse->GetResponseCode() == 200) //check si on retourne bien quelque chose
	{
		const FString ResponseBody = HttpResponse->GetContentAsString(); //recupère le contenu en string

		TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(ResponseBody); //Crée un reader avec la requete
		TArray<TSharedPtr<FJsonValue>> _result; //On va stocker dans un tarray tout les values retourner en json

		if (FJsonSerializer::Deserialize(reader, _result)) //On deserialize tout les object json
		{
			for (const TSharedPtr<FJsonValue>& JsonValue : _result) //boucle pour récupérer tout les objects
			{
				const FString _id = JsonValue->AsObject()->GetStringField(TEXT("name"));
				//On dis que si JsonValue est un objet, on récupère le field "name"
				GLog->Log(_id);
			}
		}
	}
}

void STrelloLinkSettings::Construct(const FArguments& InArgs)
{
	Http = &FHttpModule::Get();
	ChildSlot
	[
		CreateTab()
	];
}

TSharedRef<SBox> STrelloLinkSettings::CreateTab()
{
	/*TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest(); //On crée la requete

	Request->OnProcessRequestComplete().BindRaw(this, &STrelloLinkSettings::OnResponseAPI); //On met un event quand le process est fini
	FString _format = FString::Printf(TEXT("https://api.trello.com/1/boards/%s/cards?key=%s&token=%s"), *boardId, *powerUpAPI, *token); //prend le lien
	Request->SetURL(_format); //set l'url

	Request->SetVerb("GET"); //Met le post en GET
	Request->SetHeader("User-Agent", "X-UnrealEngine-Agent"); //Le header pour l'agent
	Request->SetHeader("Content-Type", "application/json"); //Le type de contenu

	Request->ProcessRequest();*/

	return SNew(SBox)
		.Padding(PADDING_8(3))
		[
			SNew(SBorder)
			.BorderBackgroundColor(FLinearColor(255, 0, 0, 1))
			[
				SNew(SGridPanel)
				.FillColumn(0, 1.0f)
				.FillRow(0, 1.0f)
				.FillRow(1, 5.0f)
				+ SGridPanel::Slot(0, 0)
				[
					SNew(SScaleBox)
					.Stretch(EStretch::ScaleToFit)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Settings"))
						.Justification(ETextJustify::Center)
					]
				]
				+ SGridPanel::Slot(0, 1)
				[
					SNew(SUniformGridPanel)
					.SlotPadding(PADDING_4(2))
					+ SUniformGridPanel::Slot(0, 0)
					[
						SNew(SBox)
						.WidthOverride(1000)
						[
							SNew(STextBlock)
							.Text(FText::FromString("Settings"))
						]
					]
				]
			]
		];
}
