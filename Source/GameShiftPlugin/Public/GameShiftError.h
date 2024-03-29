//////////////////////////////////////////////////////
// Copyright (C) Microsoft. 2018. All rights reserved.
//////////////////////////////////////////////////////


// This is automatically generated by PlayFab SDKGenerator. DO NOT modify this manually!
#pragma once

#include "CoreMinimal.h"
#include "GameShiftError.generated.h"

UENUM(BlueprintType)
enum class EGameShiftErrorCode : uint8
{
	GameShiftErrorHostnameNotFound = 1,
	GameShiftErrorConnectionTimeout,
	GameShiftErrorConnectionRefused,
	GameShiftErrorSocketError,
	GameShiftErrorSuccess = 0,

	GameShiftReferenceIdAlreadyExist,
	GameShiftMissingAPIKey,

};


USTRUCT(BlueprintType)
struct FGameShiftCppError
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 HttpCode;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	EGameShiftErrorCode ErrorCode;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString Message;

	/*
	 * This converts the PlayFabError into a human readable string describing the error.
	 * If error is not found, it will return the http code, status, and error
	 */
	FString GenerateErrorReport() const
	{
		FString output = TEXT("");
		output += TEXT("Status Code: ");
		output += FString::FromInt(HttpCode);
		output += TEXT("Message : ");
		output += Message;
		return output;
	}
};

DECLARE_DELEGATE_OneParam(FGameShiftErrorDelegate, const FGameShiftCppError&);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGameShiftErrorSignature, const FGameShiftCppError&, Error);