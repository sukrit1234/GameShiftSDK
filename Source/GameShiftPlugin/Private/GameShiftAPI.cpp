
#include "GameShiftAPI.h"
#include "GameShiftRequestHandler.h"
#include "Latents/GameShiftLatentAPI.h"

UGameShiftAPI::UGameShiftAPI()
{
	SettingPtr = MakeShareable<FGameShiftAPISettings>(new FGameShiftAPISettings());
}
bool UGameShiftAPI::FetchSecretKey(FString& OutKey) const
{
	OutKey = GetDefault<UGameShiftRuntimeSettings>()->DeveloperSecretKey;
	if (OutKey.Len() == 0)
	{
		UE_LOG(LogGameShift, Error, TEXT("You must first set your GameShift developerSecretKey to use this function (Unreal Settings Menu, or in C++ code)"));
		return false;
	}
	return true;
}
bool UGameShiftAPI::Login(const FGameShiftLoginRequest& Request, FGameShiftUserResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::POST, TEXT("/users"), Request.toJSONString(), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnFetchUserResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest(); 
}
bool UGameShiftAPI::FetchUser(const FString& RefrenceID, FGameShiftUserResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::GET, FString::Printf(TEXT("/users/%s"), *RefrenceID), TEXT(""), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnFetchUserResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();
}
bool UGameShiftAPI::FetchUsers(const FGameShiftPageRequest& Request, FGameShiftUsersResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::GET, TEXT("/users"), Request.toQueryString(), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnFetchUsersResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();
}
bool UGameShiftAPI::FetchUserAssets(const FString& RefrenceID, const FGameShiftPageRequest& Request, FGameShiftAssetsResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::GET, FString::Printf(TEXT("/users/%s/assets"), *RefrenceID), Request.toQueryString(), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnFetchAssetsResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();
}
bool UGameShiftAPI::FetchAllAssets(const FGameShiftPageRequest& Request, FGameShiftAssetsResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::GET, TEXT("/assets"), Request.toQueryString(), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnFetchAssetsResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();

}
bool UGameShiftAPI::CreateAsset(const FGameShiftCreateAssetRequest& Request, FGameShiftAssetResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::POST, TEXT("/assets"), Request.toJSONString(), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnFetchAssetResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();
}
bool UGameShiftAPI::FetchAsset(const FString& AssetId, FGameShiftAssetResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::GET, FString::Printf(TEXT("/assets/%s"), *AssetId), TEXT(""), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnFetchAssetResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();

}
bool UGameShiftAPI::TransferAsset(const FString& AssetId, const FGameShiftAssetTransferRequest& Request, FGameShiftAssetTransferResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::POST, FString::Printf(TEXT("/assets/%s/transfer"), *AssetId), Request.toJSONString(), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnAssetTransferResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();
}
bool UGameShiftAPI::LendAsset(const FString& AssetId, const FGameShiftLendAssetRequest& Request, FGameShiftLendGrantResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::POST, FString::Printf(TEXT("/assets/%s/lend"), *AssetId), Request.toJSONString(), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnLendGrantResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();

}
bool UGameShiftAPI::FetchAllAssetCollections(const FGameShiftPageRequest& Request, FGameShiftAssetCollectionsResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::GET, TEXT("/asset-collections"), Request.toQueryString(), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnAssetCollectionsResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();
}
bool UGameShiftAPI::CreateAssetCollection(const FGameShiftCreateAssetCollectionRequest& Request, FGameShiftAssetCollectionResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::POST, TEXT("/asset-collections"), Request.toJSONString(), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnAssetCollectionResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();
}
bool UGameShiftAPI::FetchAssetCollection(const FString& CollectionID, FGameShiftAssetCollectionResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::GET, FString::Printf(TEXT("/asset-collections/%s"), *CollectionID), TEXT(""), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnAssetCollectionResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();

}
bool UGameShiftAPI::FetchCollectionAssets(const FString& CollectionId, const FGameShiftPageRequest& Request, FGameShiftAssetsResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::GET, FString::Printf(TEXT("/asset-collections/%s/assets"), *CollectionId), Request.toQueryString(), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnFetchAssetsResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();

}
bool UGameShiftAPI::FetchDefaultCollectionAssets(const FGameShiftPageRequest& Request, FGameShiftAssetsResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::GET, TEXT("/asset-collections/default/assets"), Request.toQueryString(), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnFetchAssetsResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();
}

bool UGameShiftAPI::CreateAssetTemplate(const FGameShiftUpdateAssetTemplateRequest& Request, FGameShiftAssetTemplateResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::POST, TEXT("/asset-templates"), Request.toJSONString(), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnAssetTemplateResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();

}
bool UGameShiftAPI::FetchAllAssetTemplates(const FGameShiftPageRequest& Request, FGameShiftAssetTemplatesResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::GET, TEXT("/asset-templates"), Request.toQueryString(), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnAssetTemplatesResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();

}
bool UGameShiftAPI::CreateAssetFromTemplate(const FString& TemplateId, const FGameShiftDestinationUserRequest& Request, FGameShiftAssetResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::POST, FString::Printf(TEXT("/asset-templates/%s/assets"), *TemplateId), Request.toJSONString(), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnFetchAssetResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();

}
bool UGameShiftAPI::FetchAssetTemplate(const FString& TemplateId, FGameShiftAssetTemplateResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::GET, FString::Printf(TEXT("/asset-templates/%s"), *TemplateId), TEXT(""), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnAssetTemplateResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();

}
bool UGameShiftAPI::UpdateAssetTemplate(const FString& TemplateId, const FGameShiftUpdateAssetTemplateRequest& Request, FGameShiftAssetTemplateResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::PUT, FString::Printf(TEXT("/asset-templates/%s"), *TemplateId), Request.toJSONString(), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnAssetTemplateResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();

}
bool UGameShiftAPI::DeleteAssetTemplate(const FString& TemplateId, FGameShiftAssetTemplateResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::DELETE, FString::Printf(TEXT("/asset-templates/%s"), *TemplateId), TEXT(""), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnAssetTemplateResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();
}
bool UGameShiftAPI::CreatePaymentForAsset(const FString& TemplateId, const FGameShiftCreatePaymentForAssetRequest& Request, FGameShiftCreatedPaymentResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::POST, FString::Printf(TEXT("/asset-templates/%s/checkout"), *TemplateId), Request.toJSONString(), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnCreatePaymentResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();

}
bool UGameShiftAPI::FetchLendingGrant(const FString& LendingId, FGameShiftLendGrantResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::GET, FString::Printf(TEXT("/lending-grants/%s"), *LendingId), TEXT(""), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnLendGrantResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();

}
bool UGameShiftAPI::CancelLendingGrant(const FString& LendingId, const FGameShiftLenderReferenceRequest& Request, FGameShiftStringResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::DELETE, FString::Printf(TEXT("/lending-grants/%s"), *LendingId), Request.toJSONString(), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnStringResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();
}

/*
	{"id":"ae05ca78-818c-4a70-afdd-7c3feaaa2ce8",
	 "assetId":"1df7ec62-9e7d-45a2-8b62-2284318d5a23",
	 "ownerId":"ccf232ba-7ec2-4cc5-a376-2b47dcb3823b",
	 "borrowerId":"4807765c-f21b-44b1-86b7-0de300d9fe65",
	 "expiration":"2023-12-07T16:48:19.102Z",
	    "created":"2023-11-07T16:15:51.664Z",
		"status":"Accepted",
		"environment":"Development",
		"projectId":"9bc5aeee-46fc-4af3-aedf-a1d0c1f095a2"}
*/

bool UGameShiftAPI::AcceptLendingGrant(const FString& LendingId, const FGameShiftBorrowerReferenceRequest& Request, FGameShiftLendAcceptResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::POST, FString::Printf(TEXT("/lending-grants/%s/accept"), *LendingId), Request.toJSONString(), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnLendAcceptedResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();
}
bool UGameShiftAPI::ReturnAsset(const FString& LendingId, const FGameShiftBorrowerReferenceRequest& Request, FGameShiftStringResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::POST, FString::Printf(TEXT("/lending-grants/%s/return"), *LendingId), Request.toJSONString(), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnStringResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();
}
bool UGameShiftAPI::FetchPayment(const FString& PaymentId, FGameShiftPaymentResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::GET, FString::Printf(TEXT("/payments/%s"), *PaymentId), TEXT(""), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnPaymentResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();

}
bool UGameShiftAPI::FetchAllPayments(const FGameShiftPageRequest& Request, FGameShiftPaymentsResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::GET, TEXT("/payments"), Request.toQueryString(), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnPaymentsResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();

}
bool UGameShiftAPI::CreatePayment(const FGameShiftCreatePaymentRequest& Request, FGameShiftCreatedPaymentResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FString devSecretKey;
	ensure(FetchSecretKey(devSecretKey));

	auto HttpRequest = FGameShiftRequestHandler::SendRequest(SettingPtr, EVerbMode::POST, TEXT("/payments/checkout"), Request.toJSONString(), TEXT("x-api-key"), devSecretKey);
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &UGameShiftAPI::OnCreatePaymentResult, SuccessDelegate, ErrorDelegate);
	return HttpRequest->ProcessRequest();
}


void UGameShiftAPI::OnFetchUserResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftUserResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FGameShiftUserResult outResult;
	FGameShiftCppError errorResult;
	if (FGameShiftRequestHandler::DecodeRequest(Request, Response, bConnectedSuccessfully, outResult, errorResult))
		SuccessDelegate.ExecuteIfBound(outResult);
	else
		ErrorDelegate.ExecuteIfBound(errorResult);
}
void UGameShiftAPI::OnFetchUsersResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftUsersResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FGameShiftUsersResult outResult;
	FGameShiftCppError errorResult;
	if (FGameShiftRequestHandler::DecodeRequest(Request, Response, bConnectedSuccessfully, outResult, errorResult))
		SuccessDelegate.ExecuteIfBound(outResult);
	else
		ErrorDelegate.ExecuteIfBound(errorResult);
}
void UGameShiftAPI::OnFetchAssetsResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftAssetsResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FGameShiftAssetsResult outResult;
	FGameShiftCppError errorResult;
	if (FGameShiftRequestHandler::DecodeRequest(Request, Response, bConnectedSuccessfully, outResult, errorResult))
		SuccessDelegate.ExecuteIfBound(outResult);
	else
		ErrorDelegate.ExecuteIfBound(errorResult);
}
void UGameShiftAPI::OnFetchAssetResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftAssetResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FGameShiftAssetResult outResult;
	FGameShiftCppError errorResult;
	if (FGameShiftRequestHandler::DecodeRequest(Request, Response, bConnectedSuccessfully, outResult, errorResult))
		SuccessDelegate.ExecuteIfBound(outResult);
	else
		ErrorDelegate.ExecuteIfBound(errorResult);
}
void UGameShiftAPI::OnAssetTransferResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftAssetTransferResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FGameShiftAssetTransferResult outResult;
	FGameShiftCppError errorResult;
	if (FGameShiftRequestHandler::DecodeRequest(Request, Response, bConnectedSuccessfully, outResult, errorResult))
		SuccessDelegate.ExecuteIfBound(outResult);
	else
		ErrorDelegate.ExecuteIfBound(errorResult);
}
void UGameShiftAPI::OnLendAcceptedResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftLendAcceptResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FGameShiftLendAcceptResult outResult;
	FGameShiftCppError errorResult;
	if (FGameShiftRequestHandler::DecodeRequest(Request, Response, bConnectedSuccessfully, outResult, errorResult))
		SuccessDelegate.ExecuteIfBound(outResult);
	else
		ErrorDelegate.ExecuteIfBound(errorResult);
}
void UGameShiftAPI::OnLendGrantResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftLendGrantResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FGameShiftLendGrantResult outResult;
	FGameShiftCppError errorResult;
	if (FGameShiftRequestHandler::DecodeRequest(Request, Response, bConnectedSuccessfully, outResult, errorResult))
		SuccessDelegate.ExecuteIfBound(outResult);
	else
		ErrorDelegate.ExecuteIfBound(errorResult);
}
void UGameShiftAPI::OnAssetCollectionsResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftAssetCollectionsResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FGameShiftAssetCollectionsResult outResult;
	FGameShiftCppError errorResult;
	if (FGameShiftRequestHandler::DecodeRequest(Request, Response, bConnectedSuccessfully, outResult, errorResult))
		SuccessDelegate.ExecuteIfBound(outResult);
	else
		ErrorDelegate.ExecuteIfBound(errorResult);
}
void UGameShiftAPI::OnAssetCollectionResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftAssetCollectionResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FGameShiftAssetCollectionResult outResult;
	FGameShiftCppError errorResult;
	if (FGameShiftRequestHandler::DecodeRequest(Request, Response, bConnectedSuccessfully, outResult, errorResult))
		SuccessDelegate.ExecuteIfBound(outResult);
	else
		ErrorDelegate.ExecuteIfBound(errorResult);
}
void UGameShiftAPI::OnPaymentsResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftPaymentsResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FGameShiftPaymentsResult outResult;
	FGameShiftCppError errorResult;
	if (FGameShiftRequestHandler::DecodeRequest(Request, Response, bConnectedSuccessfully, outResult, errorResult))
		SuccessDelegate.ExecuteIfBound(outResult);
	else
		ErrorDelegate.ExecuteIfBound(errorResult);
}
void UGameShiftAPI::OnPaymentResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftPaymentResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FGameShiftPaymentResult outResult;
	FGameShiftCppError errorResult;
	if (FGameShiftRequestHandler::DecodeRequest(Request, Response, bConnectedSuccessfully, outResult, errorResult))
		SuccessDelegate.ExecuteIfBound(outResult);
	else
		ErrorDelegate.ExecuteIfBound(errorResult);
}
void UGameShiftAPI::OnCreatePaymentResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftCreatedPaymentResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FGameShiftCreatedPaymentResult outResult;
	FGameShiftCppError errorResult;
	if (FGameShiftRequestHandler::DecodeRequest(Request, Response, bConnectedSuccessfully, outResult, errorResult))
		SuccessDelegate.ExecuteIfBound(outResult);
	else
		ErrorDelegate.ExecuteIfBound(errorResult);
}
void UGameShiftAPI::OnAssetTemplatesResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftAssetTemplatesResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FGameShiftAssetTemplatesResult outResult;
	FGameShiftCppError errorResult;
	if (FGameShiftRequestHandler::DecodeRequest(Request, Response, bConnectedSuccessfully, outResult, errorResult))
		SuccessDelegate.ExecuteIfBound(outResult);
	else
		ErrorDelegate.ExecuteIfBound(errorResult);
}
void UGameShiftAPI::OnAssetTemplateResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftAssetTemplateResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FGameShiftAssetTemplateResult outResult;
	FGameShiftCppError errorResult;
	if (FGameShiftRequestHandler::DecodeRequest(Request, Response, bConnectedSuccessfully, outResult, errorResult))
		SuccessDelegate.ExecuteIfBound(outResult);
	else
		ErrorDelegate.ExecuteIfBound(errorResult);
}
void UGameShiftAPI::OnStringResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftStringResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate)
{
	FGameShiftStringResult outResult;
	FGameShiftCppError errorResult;
	if (FGameShiftRequestHandler::DecodeRequest(Request, Response, bConnectedSuccessfully, outResult, errorResult))
		SuccessDelegate.ExecuteIfBound(outResult);
	else
		ErrorDelegate.ExecuteIfBound(errorResult);
}



void UGameShiftAPIUtility::GameShiftUserLogin(UObject* WorldContextObject, const FGameShiftLoginRequest& Request, const FGameShiftUserResultSignature& OnCompleted, const FGameShiftErrorSignature& OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftLogin* Action = new FGameShiftLogin(Request, OnCompleted, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftFetchUser(UObject* WorldContextObject, const FString& RefrenceID, const FGameShiftUserResultSignature& OnSuccess, const FGameShiftErrorSignature& OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftFetchUser* Action = new FGameShiftFetchUser(RefrenceID, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}

void UGameShiftAPIUtility::GameShiftFetchUsers(UObject* WorldContextObject, const FGameShiftPageRequest& Request, FGameShiftUsersResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftFetchAllUsers* Action = new FGameShiftFetchAllUsers(Request, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftFetchUserAssets(UObject* WorldContextObject, const FString& RefrenceID, const FGameShiftPageRequest& Request, FGameShiftAssetsResultSignature OnSuccess,FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftFetchUserAssets* Action = new FGameShiftFetchUserAssets(RefrenceID,Request, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftFetchAllAssets(UObject* WorldContextObject, const FGameShiftPageRequest& Request,FGameShiftAssetsResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftFetchAllAssets* Action = new FGameShiftFetchAllAssets(Request, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftCreateAsset(UObject* WorldContextObject, const FGameShiftCreateAssetRequest& Request, FGameShiftAssetResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftCreateAsset* Action = new FGameShiftCreateAsset(Request, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftFetchAsset(UObject* WorldContextObject, const FString& AssetId, FGameShiftAssetResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftFetchAsset* Action = new FGameShiftFetchAsset(AssetId, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftTransferAsset(UObject* WorldContextObject, const FString& AssetId, const FGameShiftAssetTransferRequest& Request, FGameShiftAssetTransferResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftTransferAsset* Action = new FGameShiftTransferAsset(AssetId, Request, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftLendAsset(UObject* WorldContextObject, const FString& AssetId, const FGameShiftLendAssetRequest& Request, FGameShiftLendGrantResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftLendAsset* Action = new FGameShiftLendAsset(AssetId, Request, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftFetchAllAssetCollections(UObject* WorldContextObject, const FGameShiftPageRequest& Request, FGameShiftAssetCollectionsResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftFetchAllAssetCollections* Action = new FGameShiftFetchAllAssetCollections(Request, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftCreateAssetCollection(UObject* WorldContextObject, const FGameShiftCreateAssetCollectionRequest& Request, FGameShiftAssetCollectionResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftCreateAssetCollection* Action = new FGameShiftCreateAssetCollection(Request, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftFetchAssetCollection(UObject* WorldContextObject, const FString& CollectionId, FGameShiftAssetCollectionResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftFetchAssetCollection* Action = new FGameShiftFetchAssetCollection(CollectionId, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftFetchCollectionAssets(UObject* WorldContextObject, const FString& CollectionId, const FGameShiftPageRequest& Request, FGameShiftAssetsResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftFetchAllCollectionAssets* Action = new FGameShiftFetchAllCollectionAssets(CollectionId, Request, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftFetchDefaultCollectionAssets(UObject* WorldContextObject, const FGameShiftPageRequest& Request, FGameShiftAssetsResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftFetchDefaultCollectionAssets* Action = new FGameShiftFetchDefaultCollectionAssets(Request, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftCreateAssetTemplate(UObject* WorldContextObject, const FGameShiftUpdateAssetTemplateRequest& Request, FGameShiftAssetTemplateResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftCreateAssetTemplate* Action = new FGameShiftCreateAssetTemplate(Request, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftFetchAllAssetTemplates(UObject* WorldContextObject, const FGameShiftPageRequest& Request, FGameShiftAssetTemplatesResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftFetchAllAssetTemplates* Action = new FGameShiftFetchAllAssetTemplates(Request, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftCreateAssetFromTemplate(UObject* WorldContextObject, const FString& TemplateId, const FGameShiftDestinationUserRequest& Request, FGameShiftAssetResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftCreateAssetFromTemplate* Action = new FGameShiftCreateAssetFromTemplate(TemplateId,Request, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftFetchAssetTemplate(UObject* WorldContextObject, const FString& TemplateId, FGameShiftAssetTemplateResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftFetchAssetTemplate* Action = new FGameShiftFetchAssetTemplate(TemplateId,  OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftUpdateAssetTemplate(UObject* WorldContextObject, const FString& TemplateId, const FGameShiftUpdateAssetTemplateRequest& Request, FGameShiftAssetTemplateResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftUpdateAssetTemplate* Action = new FGameShiftUpdateAssetTemplate(TemplateId,Request, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftDeleteAssetTemplate(UObject* WorldContextObject, const FString& TemplateId, FGameShiftAssetTemplateResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftDeleteAssetTemplate* Action = new FGameShiftDeleteAssetTemplate(TemplateId, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftCreatePaymentForAsset(UObject* WorldContextObject, const FString& TemplateId, const FGameShiftCreatePaymentForAssetRequest& Request, FGameShiftCreatedPaymentResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftCreatePaymentForAsset* Action = new FGameShiftCreatePaymentForAsset(TemplateId, Request, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftFetchLendingGrant(UObject* WorldContextObject, const FString& LendingId, FGameShiftLendGrantResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftFetchLendingGrant* Action = new FGameShiftFetchLendingGrant(LendingId, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftCancelLendingGrant(UObject* WorldContextObject, const FString& LendingId, const FGameShiftLenderReferenceRequest& Request, FGameShiftStringResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftCancelLendingGrant* Action = new FGameShiftCancelLendingGrant(LendingId,Request, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftAcceptLendingGrant(UObject* WorldContextObject, const FString& LendingId, const FGameShiftBorrowerReferenceRequest& Request, FGameShiftLendAcceptResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftAcceptLendingGrant* Action = new FGameShiftAcceptLendingGrant(LendingId, Request, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftReturnAsset(UObject* WorldContextObject, const FString& LendingId, const FGameShiftBorrowerReferenceRequest& Request, FGameShiftStringResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftReturnAsset* Action = new FGameShiftReturnAsset(LendingId, Request, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftFetchPayment(UObject* WorldContextObject, const FString& PaymentId, FGameShiftPaymentResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftFetchPayment* Action = new FGameShiftFetchPayment(PaymentId, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftFetchAllPayments(UObject* WorldContextObject, const FGameShiftPageRequest& Request, FGameShiftPaymentsResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftFetchAllPayments* Action = new FGameShiftFetchAllPayments(Request, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
void UGameShiftAPIUtility::GameShiftCreatePayment(UObject* WorldContextObject, const FGameShiftCreatePaymentRequest& Request, FGameShiftCreatedPaymentResultSignature OnSuccess, FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FGameShiftCreatePayment* Action = new FGameShiftCreatePayment(Request, OnSuccess, OnError, LatentInfo);
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	}
}
