
#include "Latents/GameShiftLatentAPI.h"
#include "GameShiftAPI.h"

FGameShiftLogin::FGameShiftLogin(const FGameShiftLoginRequest& InRequest, const FGameShiftUserResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	:FGameShiftLatentAction(InOnError, LatentInfo)
	, Request(InRequest)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftLogin::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->Login(Request, FGameShiftUserResultDelegate::CreateRaw(this, &FGameShiftLogin::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftLogin::OnSuccessEvent(const FGameShiftUserResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}

FGameShiftFetchUser::FGameShiftFetchUser(const FString& InRefrenceID, const FGameShiftUserResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	:FGameShiftLatentAction(InOnError, LatentInfo)
	, RefrenceID(InRefrenceID)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftFetchUser::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->FetchUser(RefrenceID, FGameShiftUserResultDelegate::CreateRaw(this, &FGameShiftFetchUser::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftFetchUser::OnSuccessEvent(const FGameShiftUserResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}

FGameShiftFetchAllUsers::FGameShiftFetchAllUsers(const FGameShiftPageRequest& InRequest, const FGameShiftUsersResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	:FGameShiftLatentAction(InOnError, LatentInfo)
	, Request(InRequest)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftFetchAllUsers::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->FetchUsers(Request, FGameShiftUsersResultDelegate::CreateRaw(this, &FGameShiftFetchAllUsers::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftFetchAllUsers::OnSuccessEvent(const FGameShiftUsersResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}

FGameShiftFetchUserAssets::FGameShiftFetchUserAssets(const FString& InRefrenceID, const FGameShiftPageRequest& InRequest, const FGameShiftAssetsResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	:FGameShiftLatentAction(InOnError, LatentInfo)
	, RefrenceID(InRefrenceID)
	, Request(InRequest)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftFetchUserAssets::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->FetchUserAssets(RefrenceID, Request, FGameShiftAssetsResultDelegate::CreateRaw(this, &FGameShiftFetchUserAssets::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftFetchUserAssets::OnSuccessEvent(const FGameShiftAssetsResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}

FGameShiftCreateAsset::FGameShiftCreateAsset(const FGameShiftCreateAssetRequest& InRequest, const FGameShiftAssetResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	:FGameShiftLatentAction(InOnError, LatentInfo)
	, Request(InRequest)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftCreateAsset::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->CreateAsset(Request, FGameShiftAssetResultDelegate::CreateRaw(this, &FGameShiftCreateAsset::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftCreateAsset::OnSuccessEvent(const FGameShiftAssetResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}

FGameShiftFetchAllAssets::FGameShiftFetchAllAssets(const FGameShiftPageRequest& InRequest, const FGameShiftAssetsResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	:FGameShiftLatentAction(InOnError, LatentInfo)
	, Request(InRequest)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftFetchAllAssets::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->FetchAllAssets(Request, FGameShiftAssetsResultDelegate::CreateRaw(this, &FGameShiftFetchAllAssets::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftFetchAllAssets::OnSuccessEvent(const FGameShiftAssetsResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}

FGameShiftFetchAsset::FGameShiftFetchAsset(const FString& InAssetID, const FGameShiftAssetResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	: FGameShiftLatentAction(InOnError, LatentInfo)
	, AssetID(InAssetID)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftFetchAsset::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->FetchAsset(AssetID, FGameShiftAssetResultDelegate::CreateRaw(this, &FGameShiftFetchAsset::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftFetchAsset::OnSuccessEvent(const FGameShiftAssetResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}

FGameShiftTransferAsset::FGameShiftTransferAsset(const FString& InAssetID, const FGameShiftAssetTransferRequest& InRequest, const FGameShiftAssetTransferResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	: FGameShiftLatentAction(InOnError, LatentInfo)
	, AssetID(InAssetID)
	, Request(InRequest)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftTransferAsset::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->TransferAsset(AssetID, Request, FGameShiftAssetTransferResultDelegate::CreateRaw(this, &FGameShiftTransferAsset::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftTransferAsset::OnSuccessEvent(const FGameShiftAssetTransferResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}

FGameShiftLendAsset::FGameShiftLendAsset(const FString& InAssetID, const FGameShiftLendAssetRequest& InRequest, const FGameShiftLendGrantResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	: FGameShiftLatentAction(InOnError, LatentInfo)
	, AssetID(InAssetID)
	, Request(InRequest)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftLendAsset::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->LendAsset(AssetID, Request, FGameShiftLendGrantResultDelegate::CreateRaw(this, &FGameShiftLendAsset::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftLendAsset::OnSuccessEvent(const FGameShiftLendGrantResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}

FGameShiftFetchAllAssetCollections::FGameShiftFetchAllAssetCollections(const FGameShiftPageRequest& InRequest, const FGameShiftAssetCollectionsResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	:FGameShiftLatentAction(InOnError, LatentInfo)
	, Request(InRequest)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftFetchAllAssetCollections::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->FetchAllAssetCollections(Request, FGameShiftAssetCollectionsResultDelegate::CreateRaw(this, &FGameShiftFetchAllAssetCollections::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftFetchAllAssetCollections::OnSuccessEvent(const FGameShiftAssetCollectionsResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}

FGameShiftCreateAssetCollection::FGameShiftCreateAssetCollection(const FGameShiftCreateAssetCollectionRequest& InRequest, const FGameShiftAssetCollectionResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	:FGameShiftLatentAction(InOnError, LatentInfo)
	, Request(InRequest)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftCreateAssetCollection::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->CreateAssetCollection(Request, FGameShiftAssetCollectionResultDelegate::CreateRaw(this, &FGameShiftCreateAssetCollection::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftCreateAssetCollection::OnSuccessEvent(const FGameShiftAssetCollectionResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}

FGameShiftFetchAssetCollection::FGameShiftFetchAssetCollection(const FString& InCollectionID, const FGameShiftAssetCollectionResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	: FGameShiftLatentAction(InOnError, LatentInfo)
	, CollectionID(InCollectionID)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftFetchAssetCollection::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->FetchAssetCollection(CollectionID, FGameShiftAssetCollectionResultDelegate::CreateRaw(this, &FGameShiftFetchAssetCollection::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftFetchAssetCollection::OnSuccessEvent(const FGameShiftAssetCollectionResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}

FGameShiftFetchAllCollectionAssets::FGameShiftFetchAllCollectionAssets(const FString& InCollectionID, const FGameShiftPageRequest& InRequest, const FGameShiftAssetsResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	:FGameShiftLatentAction(InOnError, LatentInfo)
	, CollectionID(InCollectionID)
	, Request(InRequest)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftFetchAllCollectionAssets::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->FetchCollectionAssets(CollectionID, Request, FGameShiftAssetsResultDelegate::CreateRaw(this, &FGameShiftFetchAllCollectionAssets::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftFetchAllCollectionAssets::OnSuccessEvent(const FGameShiftAssetsResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}

FGameShiftFetchDefaultCollectionAssets::FGameShiftFetchDefaultCollectionAssets(const FGameShiftPageRequest& InRequest, const FGameShiftAssetsResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	:FGameShiftLatentAction(InOnError, LatentInfo)
	, Request(InRequest)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftFetchDefaultCollectionAssets::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->FetchDefaultCollectionAssets(Request, FGameShiftAssetsResultDelegate::CreateRaw(this, &FGameShiftFetchDefaultCollectionAssets::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftFetchDefaultCollectionAssets::OnSuccessEvent(const FGameShiftAssetsResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}

FGameShiftCreateAssetTemplate::FGameShiftCreateAssetTemplate(const FGameShiftUpdateAssetTemplateRequest& InRequest, const FGameShiftAssetTemplateResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	:FGameShiftLatentAction(InOnError, LatentInfo)
	, Request(InRequest)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftCreateAssetTemplate::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->CreateAssetTemplate(Request, FGameShiftAssetTemplateResultDelegate::CreateRaw(this, &FGameShiftCreateAssetTemplate::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftCreateAssetTemplate::OnSuccessEvent(const FGameShiftAssetTemplateResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}


FGameShiftFetchAllAssetTemplates::FGameShiftFetchAllAssetTemplates(const FGameShiftPageRequest& InRequest, const FGameShiftAssetTemplatesResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	:FGameShiftLatentAction(InOnError, LatentInfo)
	, Request(InRequest)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftFetchAllAssetTemplates::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->FetchAllAssetTemplates(Request, FGameShiftAssetTemplatesResultDelegate::CreateRaw(this, &FGameShiftFetchAllAssetTemplates::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftFetchAllAssetTemplates::OnSuccessEvent(const FGameShiftAssetTemplatesResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}


FGameShiftCreateAssetFromTemplate::FGameShiftCreateAssetFromTemplate(const FString& InTemplateId, const FGameShiftDestinationUserRequest& InRequest, const FGameShiftAssetResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	:FGameShiftLatentAction(InOnError, LatentInfo)
	, TemplateID(InTemplateId)
	, Request(InRequest)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftCreateAssetFromTemplate::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->CreateAssetFromTemplate(TemplateID,Request, FGameShiftAssetResultDelegate::CreateRaw(this, &FGameShiftCreateAssetFromTemplate::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftCreateAssetFromTemplate::OnSuccessEvent(const FGameShiftAssetResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}


FGameShiftFetchAssetTemplate::FGameShiftFetchAssetTemplate(const FString& InTemplateID, const FGameShiftAssetTemplateResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	: FGameShiftLatentAction(InOnError, LatentInfo)
	, TemplateID(InTemplateID)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftFetchAssetTemplate::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->FetchAssetTemplate(TemplateID, FGameShiftAssetTemplateResultDelegate::CreateRaw(this, &FGameShiftFetchAssetTemplate::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftFetchAssetTemplate::OnSuccessEvent(const FGameShiftAssetTemplateResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}


FGameShiftUpdateAssetTemplate::FGameShiftUpdateAssetTemplate(const FString& InTemplateID, const FGameShiftUpdateAssetTemplateRequest& InRequest, const FGameShiftAssetTemplateResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	: FGameShiftLatentAction(InOnError, LatentInfo)
	, TemplateID(InTemplateID)
	, Request(InRequest)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftUpdateAssetTemplate::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->UpdateAssetTemplate(TemplateID, Request, FGameShiftAssetTemplateResultDelegate::CreateRaw(this, &FGameShiftUpdateAssetTemplate::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftUpdateAssetTemplate::OnSuccessEvent(const FGameShiftAssetTemplateResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}


FGameShiftDeleteAssetTemplate::FGameShiftDeleteAssetTemplate(const FString& InTemplateID, const FGameShiftAssetTemplateResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	: FGameShiftLatentAction(InOnError, LatentInfo)
	, TemplateID(InTemplateID)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftDeleteAssetTemplate::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->DeleteAssetTemplate(TemplateID, FGameShiftAssetTemplateResultDelegate::CreateRaw(this, &FGameShiftDeleteAssetTemplate::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftDeleteAssetTemplate::OnSuccessEvent(const FGameShiftAssetTemplateResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}



FGameShiftCreatePaymentForAsset::FGameShiftCreatePaymentForAsset(const FString& InAssetID, const FGameShiftCreatePaymentForAssetRequest& InRequest, const FGameShiftCreatedPaymentResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	: FGameShiftLatentAction(InOnError, LatentInfo)
	, AssetID(InAssetID)
	, Request(InRequest)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftCreatePaymentForAsset::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->CreatePaymentForAsset(AssetID, Request, FGameShiftCreatedPaymentResultDelegate::CreateRaw(this, &FGameShiftCreatePaymentForAsset::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftCreatePaymentForAsset::OnSuccessEvent(const FGameShiftCreatedPaymentResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}

FGameShiftFetchLendingGrant::FGameShiftFetchLendingGrant(const FString& InLendingID, const FGameShiftLendGrantResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	: FGameShiftLatentAction(InOnError, LatentInfo)
	, LendingID(InLendingID)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftFetchLendingGrant::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->FetchLendingGrant(LendingID, FGameShiftLendGrantResultDelegate::CreateRaw(this, &FGameShiftFetchLendingGrant::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftFetchLendingGrant::OnSuccessEvent(const FGameShiftLendGrantResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}

FGameShiftCancelLendingGrant::FGameShiftCancelLendingGrant(const FString& InLendingID, const FGameShiftLenderReferenceRequest& InRequest, const FGameShiftStringResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	: FGameShiftLatentAction(InOnError, LatentInfo)
	, LendingID(InLendingID)
	, Request(InRequest)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftCancelLendingGrant::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->CancelLendingGrant(LendingID, Request, FGameShiftStringResultDelegate::CreateRaw(this, &FGameShiftCancelLendingGrant::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftCancelLendingGrant::OnSuccessEvent(const FGameShiftStringResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}

FGameShiftAcceptLendingGrant::FGameShiftAcceptLendingGrant(const FString& InLendingID, const FGameShiftBorrowerReferenceRequest& InRequest, const FGameShiftLendAcceptResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	: FGameShiftLatentAction(InOnError, LatentInfo)
	, LendingID(InLendingID)
	, Request(InRequest)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftAcceptLendingGrant::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->AcceptLendingGrant(LendingID, Request, FGameShiftLendAcceptResultDelegate::CreateRaw(this, &FGameShiftAcceptLendingGrant::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftAcceptLendingGrant::OnSuccessEvent(const FGameShiftLendAcceptResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}

FGameShiftReturnAsset::FGameShiftReturnAsset(const FString& InLendingID, const FGameShiftBorrowerReferenceRequest& InRequest, const FGameShiftStringResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	: FGameShiftLatentAction(InOnError, LatentInfo)
	, LendingID(InLendingID)
	, Request(InRequest)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftReturnAsset::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->ReturnAsset(LendingID, Request, FGameShiftStringResultDelegate::CreateRaw(this, &FGameShiftReturnAsset::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftReturnAsset::OnSuccessEvent(const FGameShiftStringResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}

FGameShiftCreatePayment::FGameShiftCreatePayment( const FGameShiftCreatePaymentRequest& InRequest, const FGameShiftCreatedPaymentResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	: FGameShiftLatentAction(InOnError, LatentInfo)
	, Request(InRequest)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftCreatePayment::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->CreatePayment(Request, FGameShiftCreatedPaymentResultDelegate::CreateRaw(this, &FGameShiftCreatePayment::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftCreatePayment::OnSuccessEvent(const FGameShiftCreatedPaymentResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}

FGameShiftFetchPayment::FGameShiftFetchPayment(const FString& InPaymentID, const FGameShiftPaymentResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	: FGameShiftLatentAction(InOnError, LatentInfo)
	, PaymentID(InPaymentID)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftFetchPayment::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->FetchPayment(PaymentID, FGameShiftPaymentResultDelegate::CreateRaw(this, &FGameShiftFetchPayment::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftFetchPayment::OnSuccessEvent(const FGameShiftPaymentResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}


FGameShiftFetchAllPayments::FGameShiftFetchAllPayments(const FGameShiftPageRequest& InRequest, const FGameShiftPaymentsResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	:FGameShiftLatentAction(InOnError, LatentInfo)
	, Request(InRequest)
	, OnSuccess(InOnSuccess)
{

}
bool FGameShiftFetchAllPayments::DoGameShiftRequest()
{
	GameShiftAPIPtr ApiPtr = GetAPI();
	if (ApiPtr.IsValid())
	{
		ApiPtr->FetchAllPayments(Request, FGameShiftPaymentsResultDelegate::CreateRaw(this, &FGameShiftFetchAllPayments::OnSuccessEvent), CreateErrorDelegate());
		return true;
	}
	return false;
}
void FGameShiftFetchAllPayments::OnSuccessEvent(const FGameShiftPaymentsResult& Result)
{
	bCompleted = true;
	OnSuccess.ExecuteIfBound(Result);
}
