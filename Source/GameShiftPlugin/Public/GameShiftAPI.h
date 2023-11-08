

#pragma once

#include "CoreMinimal.h"
#include "GameShiftBaseModel.h"
#include "GameShiftError.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "GameShiftAPISettings.h"
#include "GameShiftAPI.generated.h"


DECLARE_DELEGATE_OneParam(FGameShiftUserResultDelegate, const FGameShiftUserResult&);
DECLARE_DELEGATE_OneParam(FGameShiftUsersResultDelegate, const FGameShiftUsersResult&);
DECLARE_DELEGATE_OneParam(FGameShiftAssetsResultDelegate, const FGameShiftAssetsResult&);
DECLARE_DELEGATE_OneParam(FGameShiftAssetResultDelegate, const FGameShiftAssetResult&);
DECLARE_DELEGATE_OneParam(FGameShiftAssetTransferResultDelegate, const FGameShiftAssetTransferResult&);
DECLARE_DELEGATE_OneParam(FGameShiftLendGrantResultDelegate, const FGameShiftLendGrantResult&);
DECLARE_DELEGATE_OneParam(FGameShiftAssetCollectionsResultDelegate, const FGameShiftAssetCollectionsResult&);
DECLARE_DELEGATE_OneParam(FGameShiftAssetCollectionResultDelegate, const FGameShiftAssetCollectionResult&);
DECLARE_DELEGATE_OneParam(FGameShiftPaymentsResultDelegate, const FGameShiftPaymentsResult&);
DECLARE_DELEGATE_OneParam(FGameShiftPaymentResultDelegate, const FGameShiftPaymentResult&);
DECLARE_DELEGATE_OneParam(FGameShiftCreatedPaymentResultDelegate, const FGameShiftCreatedPaymentResult&);
DECLARE_DELEGATE_OneParam(FGameShiftAssetTemplatesResultDelegate, const FGameShiftAssetTemplatesResult&);
DECLARE_DELEGATE_OneParam(FGameShiftAssetTemplateResultDelegate, const FGameShiftAssetTemplateResult&);
DECLARE_DELEGATE_OneParam(FGameShiftLendAcceptResultDelegate, const FGameShiftLendAcceptResult&);
DECLARE_DELEGATE_OneParam(FGameShiftStringResultDelegate, const FGameShiftStringResult&);



class GAMESHIFTPLUGIN_API UGameShiftAPI
{

public:

	bool Login(const FGameShiftLoginRequest& Request, FGameShiftUserResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool FetchUser(const FString& RefrenceID, FGameShiftUserResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool FetchUsers(const FGameShiftPageRequest& Request, FGameShiftUsersResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool FetchUserAssets(const FString& RefrenceID, const FGameShiftPageRequest& Request, FGameShiftAssetsResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);

	bool FetchAllAssets(const FGameShiftPageRequest& Request, FGameShiftAssetsResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool CreateAsset(const FGameShiftCreateAssetRequest& Request, FGameShiftAssetResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool FetchAsset(const FString& AssetId, FGameShiftAssetResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool TransferAsset(const FString& AssetId, const FGameShiftAssetTransferRequest& Request, FGameShiftAssetTransferResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool LendAsset(const FString& AssetId, const FGameShiftLendAssetRequest& Request, FGameShiftLendGrantResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);

	bool FetchAllAssetCollections(const FGameShiftPageRequest& Request, FGameShiftAssetCollectionsResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool CreateAssetCollection(const FGameShiftCreateAssetCollectionRequest& Request, FGameShiftAssetCollectionResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool FetchAssetCollection(const FString& CollectionId, FGameShiftAssetCollectionResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool FetchCollectionAssets(const FString& CollectionId, const FGameShiftPageRequest& Request, FGameShiftAssetsResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool FetchDefaultCollectionAssets(const FGameShiftPageRequest& Request, FGameShiftAssetsResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);

	bool CreateAssetTemplate(const FGameShiftUpdateAssetTemplateRequest& Request, FGameShiftAssetTemplateResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool FetchAllAssetTemplates(const FGameShiftPageRequest& Request, FGameShiftAssetTemplatesResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool CreateAssetFromTemplate(const FString& TemplateId, const FGameShiftDestinationUserRequest& Request, FGameShiftAssetResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool FetchAssetTemplate(const FString& TemplateId, FGameShiftAssetTemplateResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool UpdateAssetTemplate(const FString& TemplateId, const FGameShiftUpdateAssetTemplateRequest& Request, FGameShiftAssetTemplateResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool DeleteAssetTemplate(const FString& TemplateId, FGameShiftAssetTemplateResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool CreatePaymentForAsset(const FString& TemplateId, const FGameShiftCreatePaymentForAssetRequest& Request, FGameShiftCreatedPaymentResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool FetchLendingGrant(const FString& LendingId, FGameShiftLendGrantResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool CancelLendingGrant(const FString& LendingId, const FGameShiftLenderReferenceRequest& Request, FGameShiftStringResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool AcceptLendingGrant(const FString& LendingId, const FGameShiftBorrowerReferenceRequest& Request, FGameShiftLendAcceptResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool ReturnAsset(const FString& LendingId, const FGameShiftBorrowerReferenceRequest& Request, FGameShiftStringResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);

	bool FetchPayment(const FString& PaymentId, FGameShiftPaymentResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool FetchAllPayments(const FGameShiftPageRequest& Request, FGameShiftPaymentsResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	bool CreatePayment(const FGameShiftCreatePaymentRequest& Request, FGameShiftCreatedPaymentResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);

	UGameShiftAPI();

protected:

	bool FetchSecretKey(FString& OutKey) const;
	void OnFetchUserResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftUserResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	void OnFetchUsersResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftUsersResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	void OnFetchAssetsResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftAssetsResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	void OnFetchAssetResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftAssetResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	void OnAssetTransferResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftAssetTransferResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	void OnLendGrantResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftLendGrantResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	void OnLendAcceptedResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftLendAcceptResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);

	void OnAssetCollectionsResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftAssetCollectionsResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	void OnAssetCollectionResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftAssetCollectionResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	void OnPaymentsResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftPaymentsResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	void OnPaymentResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftPaymentResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	void OnCreatePaymentResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftCreatedPaymentResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	void OnAssetTemplatesResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftAssetTemplatesResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);
	void OnAssetTemplateResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftAssetTemplateResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);

	void OnStringResult(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully, FGameShiftStringResultDelegate SuccessDelegate, FGameShiftErrorDelegate ErrorDelegate);


	TSharedPtr<FGameShiftAPISettings> SettingPtr;
};


UCLASS()
class UGameShiftAPIUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftUserLogin(UObject* WorldContextObject, const FGameShiftLoginRequest& Request, UPARAM(DisplayName = "OnSuccess") const FGameShiftUserResultSignature& OnSuccess, UPARAM(DisplayName = "OnError") const FGameShiftErrorSignature& OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftFetchUser(UObject* WorldContextObject, const FString& RefrenceID, UPARAM(DisplayName = "OnSuccess") const FGameShiftUserResultSignature& OnSuccess, UPARAM(DisplayName = "OnError") const FGameShiftErrorSignature& OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftFetchUsers(UObject* WorldContextObject, const FGameShiftPageRequest& Request, UPARAM(DisplayName = "OnSuccess") FGameShiftUsersResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftFetchUserAssets(UObject* WorldContextObject, const FString& RefrenceID, const FGameShiftPageRequest& Request, UPARAM(DisplayName = "OnSuccess")  FGameShiftAssetsResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftFetchAllAssets(UObject* WorldContextObject, const FGameShiftPageRequest& Request, UPARAM(DisplayName = "OnSuccess")  FGameShiftAssetsResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftCreateAsset(UObject* WorldContextObject, const FGameShiftCreateAssetRequest& Request, UPARAM(DisplayName = "OnSuccess")  FGameShiftAssetResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftFetchAsset(UObject* WorldContextObject, const FString& AssetId, UPARAM(DisplayName = "OnSuccess")  FGameShiftAssetResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftTransferAsset(UObject* WorldContextObject, const FString& AssetId, const FGameShiftAssetTransferRequest& Request, UPARAM(DisplayName = "OnSuccess")  FGameShiftAssetTransferResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftLendAsset(UObject* WorldContextObject, const FString& AssetId, const FGameShiftLendAssetRequest& Request, UPARAM(DisplayName = "OnSuccess")  FGameShiftLendGrantResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftFetchAllAssetCollections(UObject* WorldContextObject, const FGameShiftPageRequest& Request, UPARAM(DisplayName = "OnSuccess") FGameShiftAssetCollectionsResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftCreateAssetCollection(UObject* WorldContextObject, const FGameShiftCreateAssetCollectionRequest& Request, FGameShiftAssetCollectionResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftFetchAssetCollection(UObject* WorldContextObject, const FString& CollectionId, UPARAM(DisplayName = "OnSuccess") FGameShiftAssetCollectionResultSignature OnSuccess, UPARAM(DisplayName = "OnError") FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftFetchCollectionAssets(UObject* WorldContextObject, const FString& CollectionId, const FGameShiftPageRequest& Request, UPARAM(DisplayName = "OnSuccess")  FGameShiftAssetsResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftFetchDefaultCollectionAssets(UObject* WorldContextObject, const FGameShiftPageRequest& Request, FGameShiftAssetsResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftCreateAssetTemplate(UObject* WorldContextObject, const FGameShiftUpdateAssetTemplateRequest& Request, UPARAM(DisplayName = "OnSuccess") FGameShiftAssetTemplateResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftFetchAllAssetTemplates(UObject* WorldContextObject, const FGameShiftPageRequest& Request, UPARAM(DisplayName = "OnSuccess")  FGameShiftAssetTemplatesResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftCreateAssetFromTemplate(UObject* WorldContextObject, const FString& TemplateId, const FGameShiftDestinationUserRequest& Request, UPARAM(DisplayName = "OnSuccess")  FGameShiftAssetResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftFetchAssetTemplate(UObject* WorldContextObject, const FString& TemplateId, UPARAM(DisplayName = "OnSuccess")  FGameShiftAssetTemplateResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftUpdateAssetTemplate(UObject* WorldContextObject, const FString& TemplateId, const FGameShiftUpdateAssetTemplateRequest& Request, UPARAM(DisplayName = "OnSuccess")  FGameShiftAssetTemplateResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftDeleteAssetTemplate(UObject* WorldContextObject, const FString& TemplateId, UPARAM(DisplayName = "OnSuccess")  FGameShiftAssetTemplateResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftCreatePaymentForAsset(UObject* WorldContextObject, const FString& TemplateId, const FGameShiftCreatePaymentForAssetRequest& Request, UPARAM(DisplayName = "OnSuccess")  FGameShiftCreatedPaymentResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftFetchLendingGrant(UObject* WorldContextObject, const FString& LendingId, UPARAM(DisplayName = "OnSuccess")  FGameShiftLendGrantResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftCancelLendingGrant(UObject* WorldContextObject, const FString& LendingId, const FGameShiftLenderReferenceRequest& Request, UPARAM(DisplayName = "OnSuccess")  FGameShiftStringResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftAcceptLendingGrant(UObject* WorldContextObject, const FString& LendingId, const FGameShiftBorrowerReferenceRequest& Request, FGameShiftLendAcceptResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftReturnAsset(UObject* WorldContextObject, const FString& LendingId, const FGameShiftBorrowerReferenceRequest& Request, UPARAM(DisplayName = "OnSuccess")  FGameShiftStringResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftFetchPayment(UObject* WorldContextObject, const FString& PaymentId, UPARAM(DisplayName = "OnSuccess")  FGameShiftPaymentResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftFetchAllPayments(UObject* WorldContextObject, const FGameShiftPageRequest& Request, UPARAM(DisplayName = "OnSuccess")  FGameShiftPaymentsResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"), Category = "Game Shift API")
		static void GameShiftCreatePayment(UObject* WorldContextObject, const FGameShiftCreatePaymentRequest& Request, UPARAM(DisplayName = "OnSuccess")  FGameShiftCreatedPaymentResultSignature OnSuccess, UPARAM(DisplayName = "OnError")  FGameShiftErrorSignature OnError, FLatentActionInfo LatentInfo);
};