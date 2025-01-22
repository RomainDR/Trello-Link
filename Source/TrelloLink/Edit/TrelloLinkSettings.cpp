#include "TrelloLinkSettings.h"

#include "Interfaces/IHttpResponse.h"
#include "Interfaces/IPluginManager.h"
#include "TrelloLink/Utils/TrelloLinkMacro.h"
#include "TrelloLink/Utils/TrelloUtils.h"
#include "Widgets/Layout/SScaleBox.h"
#include "Widgets/Layout/SUniformGridPanel.h"


FReply STrelloLinkSettings::TestConnection()
{
	TSharedPtr<IHttpRequest> Request = Http->CreateRequest(); //On crée la requete

	const FString powerUpAPI = powerUpField.Get()->GetText().ToString();
	const FString token = tokenField.Get()->GetText().ToString();
	const FString boardId = idBoardField.Get()->GetText().ToString();
	
	Request->OnProcessRequestComplete().BindRaw(this, &STrelloLinkSettings::OnResponseAPI); //On met un event quand le process est fini
	FString _format = FString::Printf(TEXT("https://api.trello.com/1/boards/%s?key=%s&token=%s"), *boardId, *powerUpAPI, *token); //prend le lien
	Request->SetURL(_format); //set l'url

	Request->SetVerb("GET"); //Met le post en GET
	Request->SetHeader("User-Agent", "X-UnrealEngine-Agent"); //Le header pour l'agent
	Request->SetHeader("Content-Type", "application/json"); //Le type de contenu

	Request->ProcessRequest();	
	return FReply::Handled();
}

FReply STrelloLinkSettings::SaveSettings()
{
	return FReply::Unhandled();
}

void STrelloLinkSettings::OnResponseAPI(TSharedPtr<IHttpRequest> HttpRequest, TSharedPtr<IHttpResponse> HttpResponse,
                                        bool bArg)
{
	if (HttpResponse->GetResponseCode() == 200)
	{
		TSharedPtr<FJsonObject> JsonObject;
		const FString ResponseBody = HttpResponse->GetContentAsString();

		TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(ResponseBody);
		TSharedPtr<FJsonValue> _result;
		
		if (FJsonSerializer::Deserialize(reader, _result))
		{			
				const FString _name	= _result->AsObject()->GetStringField(TEXT("name"));			
				TrelloUtils::SendPopupSuccess("Success", FORMAT(FString("Successful connection to '{0}' board"), _name));
		}		
		else
		{
			TrelloUtils::SendPopupError("Deserialize failed", "Error during deserialize of json");
		}
	}
	else
	{
		TrelloUtils::SendPopupError("Connection Failed", FORMAT(FString("Connection Failed: \nResponse code: {0}.\nError: {1}"), FString::FromInt(HttpResponse->GetResponseCode()), HttpResponse->GetContentAsString()));
	}
	
	/*TSharedPtr<FJsonObject> JsonObject; //Crée un json object
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
	}*/

	
}

void STrelloLinkSettings::Construct(const FArguments& InArgs)
{
	Http = &FHttpModule::Get();
	ChildSlot
	[
		CreateTab()
	];
}

TSharedRef<SVerticalBox> STrelloLinkSettings::CreateSection(TSharedPtr<SEditableTextBox>& _assign,
                                                            const FString& _title, const FString& _description,
                                                            const FString& _placeholder) const
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.HAlign(HCenter)
		[
			SNew(SScaleBox)
			.Stretch(EStretch::Fill)
			[
				SNew(STextBlock)
				.Text(FText::FromString(_title))
				.Font(FONT_BOLD(16))
			]
		]
		+ SVerticalBox::Slot()
		.HAlign(HCenter)
		[
			SNew(SScaleBox)
			.Stretch(EStretch::Fill)
			[
				SNew(STextBlock)
				.Text(FText::FromString(_description))
				.Font(FONT_ITALIC(12))
			]
		]
		+ SVerticalBox::Slot()
		.FillHeight(.75f)
		[
			SNew(SScaleBox)
			.Stretch(EStretch::Fill)
			[
				SAssignNew(_assign, SEditableTextBox)
				.HintText(FText::FromString(_placeholder))
			]
		];
}

TSharedRef<SBox> STrelloLinkSettings::CreateTab()
{
	return SNew(SBox)
		.Padding(PADDING_8(3))
		[
			SNew(SBorder)
			.BorderBackgroundColor(FLinearColor(0, 255, 0))
			[
				SNew(SGridPanel)
				.FillColumn(0, 1.f)
				.FillRow(0, 1.f)
				.FillRow(1, 5.f)
				.FillRow(2, .5f)
				+ SGridPanel::Slot(0, 0)
				[
					SNew(SScaleBox)
					.Stretch(EStretch::ScaleToFit)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Settings"))
						.Font(FONT_BOLD(32))
						.Justification(ETextJustify::Center)
					]
				]
				+ SGridPanel::Slot(0, 1)
				[
					SNew(SUniformGridPanel)
					.SlotPadding(PADDING_4(10))
					+ SUniformGridPanel::Slot(0, 0)
					[
						CreateSection(powerUpField, "Power Up Token", "Enter the token key of your power up API",
						              "Enter the token of power up")
					]
					+ SUniformGridPanel::Slot(0, 1)
					[
						CreateSection(tokenField, "Personal Token",
						              "This is a key genereated only for you. It must never be shared !",
						              "Enter the personal token")
					]
					+ SUniformGridPanel::Slot(0, 2)
					[
						CreateSection(idBoardField, "Board ID", "Enter the ID of the board", "Enter the id of board")
					]
				]
				+ SGridPanel::Slot(0, 2)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.FillWidth(1.0f)
					[
						SNew(SScaleBox)
						.Stretch(EStretch::ScaleToFit)
						[
							TrelloUtils::CreateButton("Test connection",
							                          FOnClicked::CreateRaw(this, &STrelloLinkSettings::TestConnection))
						]
					]
					+ SHorizontalBox::Slot()
					.FillWidth(1.0f)
					[
						SNew(SScaleBox)
						.Stretch(EStretch::ScaleToFit)
						[
							TrelloUtils::CreateButton("Save",
							                          FOnClicked::CreateRaw(this, &STrelloLinkSettings::SaveCredentials))
						]
					]
				]
			]
		];
}
