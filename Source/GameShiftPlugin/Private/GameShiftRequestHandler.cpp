//////////////////////////////////////////////////////
// Copyright (C) Microsoft. 2018. All rights reserved.
//////////////////////////////////////////////////////


#include "GameShiftRequestHandler.h"
#include "Serialization/JsonSerializer.h"
#include "GameShiftError.h"
#include "GameShift.h"

int FGameShiftRequestHandler::pendingCalls = 0;
int FGameShiftRequestHandler::GetPendingCalls()
{
    return FGameShiftRequestHandler::pendingCalls;
}

TSharedRef<IHttpRequest, ESPMode::ThreadSafe> FGameShiftRequestHandler::SendRequest(TSharedPtr<FGameShiftAPISettings> settings, EVerbMode Verb, const FString& urlPath, const FString& callBody, const FString& authKey, const FString& authValue)
{
	FString fullUrl = settings.IsValid() ? settings->GeneratePfUrl(urlPath) : urlPath;
    return SendFullUrlRequest(Verb,fullUrl, callBody, authKey, authValue);
}

TSharedRef<IHttpRequest, ESPMode::ThreadSafe> FGameShiftRequestHandler::SendFullUrlRequest(EVerbMode Verb, const FString& fullUrl, const FString& callBody, const FString& authKey, const FString& authValue)
{
	FGameShiftRequestHandler::pendingCalls += 1;
	bool bIsGetMethod = EVerbMode::GET == Verb;
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb(GetVerbString(Verb));
	if (bIsGetMethod && (callBody.Len() > 0))
		HttpRequest->SetURL(fullUrl + "?" + callBody);
	else
		HttpRequest->SetURL(fullUrl);

	HttpRequest->SetHeader(TEXT("accept"), TEXT("application/json"));
	if (authKey != TEXT(""))
        HttpRequest->SetHeader(authKey, authValue);
	if (!callBody.IsEmpty() && (callBody.Len() > 0) && !bIsGetMethod)
	{
		HttpRequest->SetHeader(TEXT("content-type"), TEXT("application/json"));
		HttpRequest->SetContentAsString(callBody);
	}
    return HttpRequest;
}

bool FGameShiftRequestHandler::DecodeRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FGameShiftBaseModel& OutResult, FGameShiftCppError& OutError)
{
	FGameShiftRequestHandler::pendingCalls -= 1;

	/*
		{
		  "referenceId": "youshoppu1111",
		  "address": "DuFvBi2f1PbxJqVQfjwXqi6qixVGGugaN1BzvL9zSNnM",
		  "email": "youshoppu@gmail.com"
		}
	*/

    FString ResponseStr, ErrorStr;
    if (bSucceeded && HttpResponse.IsValid())
    {
        if (EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
        {
            // Create the Json parser
            ResponseStr = HttpResponse->GetContentAsString();
            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<> > JsonReader = TJsonReaderFactory<>::Create(ResponseStr);

            if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
            {
                if (FGameShiftRequestHandler::DecodeError(JsonObject, OutError))
                    return false;
				return OutResult.readFromValue(JsonObject);
            }
			else
				return OutResult.readFromString(ResponseStr);
		}
        else
        {
            // Create the Json parser
            ResponseStr = HttpResponse->GetContentAsString();
            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<> > JsonReader = TJsonReaderFactory<>::Create(ResponseStr);
            if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
            {
                if (FGameShiftRequestHandler::DecodeError(JsonObject, OutError))
                {
                    return false;
                }
            }
        }
    }

    OutError.HttpCode = 408;
    OutError.ErrorCode = EGameShiftErrorCode::GameShiftErrorConnectionTimeout;
    OutError.Message = TEXT("Request Timeout or null response");

    return false;
}

bool FGameShiftRequestHandler::DecodeError(TSharedPtr<FJsonObject> JsonObject, FGameShiftCppError& OutError)
{
	/*
	Example Error Code
	{
		  "statusCode": 409,
		  "message": "A user with that reference id already exists"
	}
	*/

    // check if returned json indicates an error
    if (JsonObject->HasField(TEXT("statusCode")))
    {
		JsonObject->TryGetNumberField(TEXT("statusCode"), OutError.HttpCode);
		JsonObject->TryGetStringField(TEXT("message"), OutError.Message);
		return true;
    }

    return false;
}
