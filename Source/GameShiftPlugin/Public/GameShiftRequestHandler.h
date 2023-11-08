//////////////////////////////////////////////////////
// Copyright (C) Microsoft. 2018. All rights reserved.
//////////////////////////////////////////////////////


#pragma once

#include "CoreMinimal.h"
#include "GameShiftAPISettings.h"
#include "GameShiftBaseModel.h"
#include "GameShiftError.h"
#include "Http.h"

class FGameShiftRequestHandler
{
private:
	static int pendingCalls;
public:
	static int GetPendingCalls();
	static TSharedRef<IHttpRequest, ESPMode::ThreadSafe> SendRequest(TSharedPtr<FGameShiftAPISettings> settings, EVerbMode Verb, const FString& urlPath, const FString& callBody, const FString& authKey, const FString& authValue);
	static TSharedRef<IHttpRequest, ESPMode::ThreadSafe> SendFullUrlRequest(EVerbMode Verb, const FString& fullUrl, const FString& callBody, const FString& authKey, const FString& authValue);
	static bool DecodeRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FGameShiftBaseModel& OutResult, FGameShiftCppError& OutError);
	static bool DecodeError(TSharedPtr<FJsonObject> JsonObject, FGameShiftCppError& OutError);
};