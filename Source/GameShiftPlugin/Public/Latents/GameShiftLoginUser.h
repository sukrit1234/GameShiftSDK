#pragma once

#include "CoreMinimal.h"
#include "GameShiftLatentActions.h"

class FGameShiftLogin : public FGameShiftLatentAction
{
public:

	FGameShiftLogin(const FGameShiftLoginRequest& InRequest, const FGameShiftUserResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FGameShiftLoginRequest Request;
	FGameShiftUserResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftUserResult& Result);
};

class FGameShiftFetchUser : public FGameShiftLatentAction
{
public:

	FGameShiftFetchUser(const FString& InRefrenceID, const FGameShiftUserResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FString RefrenceID;
	FGameShiftUserResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftUserResult& Result);
};

class FGameShiftFetchAllUsers : public FGameShiftLatentAction
{
public:

	FGameShiftFetchAllUsers(const FGameShiftPageRequest& InRequest, const FGameShiftUsersResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FGameShiftPageRequest Request;
	FGameShiftUsersResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftUsersResult& Result);
};

class FGameShiftFetchUserAssets : public FGameShiftLatentAction
{
public:

	FGameShiftFetchUserAssets(const FString& InRefrenceID,const FGameShiftPageRequest& InRequest, const FGameShiftAssetsResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FString RefrenceID;
	FGameShiftPageRequest Request;
	FGameShiftAssetsResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftAssetsResult& Result);
};

class FGameShiftCreateAsset : public FGameShiftLatentAction
{
public:

	FGameShiftCreateAsset(const FGameShiftCreateAssetRequest& InRequest, const FGameShiftAssetResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FGameShiftCreateAssetRequest Request;
	FGameShiftAssetResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftAssetResult& Result);
};

class FGameShiftFetchAllAssets : public FGameShiftLatentAction
{
public:

	FGameShiftFetchAllAssets(const FGameShiftPageRequest& InRequest, const FGameShiftAssetsResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FGameShiftPageRequest Request;
	FGameShiftAssetsResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftAssetsResult& Result);
};

class FGameShiftFetchAsset : public FGameShiftLatentAction
{
public:

	FGameShiftFetchAsset(const FString& InAssetID, const FGameShiftAssetResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FString AssetID;
	FGameShiftAssetResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftAssetResult& Result);
};

class FGameShiftTransferAsset : public FGameShiftLatentAction
{
public:

	FGameShiftTransferAsset(const FString& InAssetId, const FGameShiftAssetTransferRequest& InRequest, const FGameShiftAssetTransferResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FString AssetID;
	FGameShiftAssetTransferRequest Request;
	FGameShiftAssetTransferResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftAssetTransferResult& Result);
};

class FGameShiftLendAsset : public FGameShiftLatentAction
{
public:

	FGameShiftLendAsset(const FString& InAssetId, const FGameShiftLendAssetRequest& InRequest, const FGameShiftLendGrantResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FString AssetID;
	FGameShiftLendAssetRequest Request;
	FGameShiftLendGrantResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftLendGrantResult& Result);
};

class FGameShiftFetchAllAssetCollections : public FGameShiftLatentAction
{
public:

	FGameShiftFetchAllAssetCollections(const FGameShiftPageRequest& InRequest, const FGameShiftAssetCollectionsResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FGameShiftPageRequest Request;
	FGameShiftAssetCollectionsResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftAssetCollectionsResult& Result);
};

class FGameShiftCreateAssetCollection : public FGameShiftLatentAction
{
public:

	FGameShiftCreateAssetCollection(const FGameShiftCreateAssetCollectionRequest& InRequest, const FGameShiftAssetCollectionResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FGameShiftCreateAssetCollectionRequest Request;
	FGameShiftAssetCollectionResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftAssetCollectionResult& Result);
};

class FGameShiftFetchAssetCollection : public FGameShiftLatentAction
{
public:

	FGameShiftFetchAssetCollection(const FString& InCollectionID, const FGameShiftAssetCollectionResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FString CollectionID;
	FGameShiftAssetCollectionResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftAssetCollectionResult& Result);
};

class FGameShiftFetchAllCollectionAssets : public FGameShiftLatentAction
{
public:

	FGameShiftFetchAllCollectionAssets(const FString& InCollectionId, const FGameShiftPageRequest& InRequest, const FGameShiftAssetsResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;


	FString CollectionID;
	FGameShiftPageRequest Request;
	FGameShiftAssetsResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftAssetsResult& Result);
};

class FGameShiftFetchDefaultCollectionAssets : public FGameShiftLatentAction
{
public:

	FGameShiftFetchDefaultCollectionAssets(const FGameShiftPageRequest& InRequest, const FGameShiftAssetsResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FGameShiftPageRequest Request;
	FGameShiftAssetsResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftAssetsResult& Result);
};

class FGameShiftCreateAssetTemplate : public FGameShiftLatentAction
{
public:

	FGameShiftCreateAssetTemplate(const FGameShiftUpdateAssetTemplateRequest& InRequest, const FGameShiftAssetTemplateResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FGameShiftUpdateAssetTemplateRequest Request;
	FGameShiftAssetTemplateResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftAssetTemplateResult& Result);
};

class FGameShiftFetchAllAssetTemplates : public FGameShiftLatentAction
{
public:

	FGameShiftFetchAllAssetTemplates(const FGameShiftPageRequest& InRequest, const FGameShiftAssetTemplatesResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FGameShiftPageRequest Request;
	FGameShiftAssetTemplatesResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftAssetTemplatesResult& Result);
};

class FGameShiftCreateAssetFromTemplate : public FGameShiftLatentAction
{
public:

	FGameShiftCreateAssetFromTemplate(const FString& InTemplateId, const FGameShiftDestinationUserRequest& InRequest, const FGameShiftAssetResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FString TemplateID;
	FGameShiftDestinationUserRequest Request;
	FGameShiftAssetResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftAssetResult& Result);
};

class FGameShiftFetchAssetTemplate : public FGameShiftLatentAction
{
public:

	FGameShiftFetchAssetTemplate(const FString& InTemplateID, const FGameShiftAssetTemplateResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FString TemplateID;
	FGameShiftAssetTemplateResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftAssetTemplateResult& Result);
};

class FGameShiftUpdateAssetTemplate : public FGameShiftLatentAction
{
public:

	FGameShiftUpdateAssetTemplate(const FString& InTemplateID,const FGameShiftUpdateAssetTemplateRequest& InRequest, const FGameShiftAssetTemplateResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FString TemplateID;
	FGameShiftUpdateAssetTemplateRequest Request;
	FGameShiftAssetTemplateResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftAssetTemplateResult& Result);
};

class FGameShiftDeleteAssetTemplate : public FGameShiftLatentAction
{
public:

	FGameShiftDeleteAssetTemplate(const FString& InTemplateID, const FGameShiftAssetTemplateResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FString TemplateID;
	FGameShiftAssetTemplateResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftAssetTemplateResult& Result);
};

class FGameShiftCreatePaymentForAsset : public FGameShiftLatentAction
{
public:

	FGameShiftCreatePaymentForAsset(const FString& InAssetID, const FGameShiftCreatePaymentForAssetRequest& InRequest, const FGameShiftCreatedPaymentResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FString AssetID;
	FGameShiftCreatePaymentForAssetRequest Request;
	FGameShiftCreatedPaymentResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftCreatedPaymentResult& Result);
};

class FGameShiftFetchLendingGrant : public FGameShiftLatentAction
{
public:

	FGameShiftFetchLendingGrant(const FString& InLendingID, const FGameShiftLendGrantResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FString LendingID;
	FGameShiftLendGrantResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftLendGrantResult& Result);
};

class FGameShiftCancelLendingGrant : public FGameShiftLatentAction
{
public:

	FGameShiftCancelLendingGrant(const FString& InLendingID, const FGameShiftLenderReferenceRequest& InRequest, const FGameShiftStringResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FString LendingID;
	FGameShiftLenderReferenceRequest Request;
	FGameShiftStringResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftStringResult& Result);
};

class FGameShiftAcceptLendingGrant : public FGameShiftLatentAction
{
public:

	FGameShiftAcceptLendingGrant(const FString& InLendingID, const FGameShiftBorrowerReferenceRequest& InRequest, const FGameShiftLendAcceptResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FString LendingID;
	FGameShiftBorrowerReferenceRequest Request;
	FGameShiftLendAcceptResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftLendAcceptResult& Result);
};

class FGameShiftReturnAsset : public FGameShiftLatentAction
{
public:

	FGameShiftReturnAsset(const FString& InLendingID, const FGameShiftBorrowerReferenceRequest& InRequest, const FGameShiftStringResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FString LendingID;
	FGameShiftBorrowerReferenceRequest Request;
	FGameShiftStringResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftStringResult& Result);
};

class FGameShiftCreatePayment : public FGameShiftLatentAction
{
public:

	FGameShiftCreatePayment(const FGameShiftCreatePaymentRequest& InRequest, const FGameShiftCreatedPaymentResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FString AssetID;
	FGameShiftCreatePaymentRequest Request;
	FGameShiftCreatedPaymentResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftCreatedPaymentResult& Result);
};

class FGameShiftFetchPayment : public FGameShiftLatentAction
{
public:

	FGameShiftFetchPayment(const FString& InPaymentID, const FGameShiftPaymentResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FString PaymentID;
	FGameShiftPaymentResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftPaymentResult& Result);
};

class FGameShiftFetchAllPayments : public FGameShiftLatentAction
{
public:

	FGameShiftFetchAllPayments(const FGameShiftPageRequest& InRequest, const FGameShiftPaymentsResultSignature& InOnSuccess, const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	virtual bool DoGameShiftRequest() override;

	FGameShiftPageRequest Request;
	FGameShiftPaymentsResultSignature OnSuccess;
	void OnSuccessEvent(const FGameShiftPaymentsResult& Result);
};