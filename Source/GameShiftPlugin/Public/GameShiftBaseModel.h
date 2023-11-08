//////////////////////////////////////////////////////
// Copyright (C) Microsoft. 2018. All rights reserved.
//////////////////////////////////////////////////////


#pragma once

#include "CoreMinimal.h"
#include "GameShiftTypes.h"
#include <Policies/CondensedJsonPrintPolicy.h>
#include "GameShiftBaseModel.generated.h"



	USTRUCT(BlueprintInternalUseOnly)
	struct FGameShiftBaseModel
    {
		GENERATED_BODY()

        virtual ~FGameShiftBaseModel() {}
		virtual void writeJSON(JsonWriter& Json) const {}
		virtual void writeQuery(TArray<FString>& Queries) const {}
		virtual bool readFromString(const FString& String) { return false; };
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) { return false; }
        virtual bool readFromValue(const TSharedPtr<FJsonValue>& value) { return false; };
        FString toJSONString() const;
		FString toQueryString() const;
    };

	struct GAMESHIFTPLUGIN_API FJsonKeeper : public FGameShiftBaseModel
	{
	private:
		TSharedRef<class FJsonValue> JsonValue; // Reference so that any time this struct is avaiable, the JsonValue is aswell, even if a FJsonValueNull

	public:
		FJsonKeeper() : JsonValue(MakeShareable(new FJsonValueNull())) {}
		FJsonKeeper(const TSharedPtr<class FJsonValue>& val) : JsonValue(val.ToSharedRef()) {}
		FJsonKeeper(const TSharedPtr<class FJsonObject>& val) : JsonValue(MakeShareable(new FJsonValueObject(val))) {}
		FJsonKeeper(const FString& val) : JsonValue(MakeShareable(new FJsonValueString(val))) {}
		FJsonKeeper(const bool& val) : JsonValue(MakeShareable(new FJsonValueBoolean(val))) {}
		FJsonKeeper(const int8& val) : JsonValue(MakeShareable(new FJsonValueNumber(val))) {}
		FJsonKeeper(const int16& val) : JsonValue(MakeShareable(new FJsonValueNumber(val))) {}
		FJsonKeeper(const int32& val) : JsonValue(MakeShareable(new FJsonValueNumber(val))) {}
		FJsonKeeper(const int64& val) : JsonValue(MakeShareable(new FJsonValueNumber(val))) {}
		FJsonKeeper(const uint8& val) : JsonValue(MakeShareable(new FJsonValueNumber(val))) {}
		FJsonKeeper(const uint16& val) : JsonValue(MakeShareable(new FJsonValueNumber(val))) {}
		FJsonKeeper(const uint32& val) : JsonValue(MakeShareable(new FJsonValueNumber(val))) {}
		FJsonKeeper(const uint64& val) : JsonValue(MakeShareable(new FJsonValueNumber(val))) {}
		FJsonKeeper(const float& val) : JsonValue(MakeShareable(new FJsonValueNumber(val))) {}
		FJsonKeeper(const double& val) : JsonValue(MakeShareable(new FJsonValueNumber(val))) {}

		bool notNull() const { return !isNull(); }
		bool isNull() const { return JsonValue->IsNull(); }

		FJsonKeeper& operator=(const TSharedPtr<class FJsonValue>& val) { JsonValue = val.ToSharedRef(); return *this; }
		FJsonKeeper& operator=(const TSharedPtr<class FJsonObject>& val) { JsonValue = MakeShareable(new FJsonValueObject(val)); return *this; }
		FJsonKeeper& operator=(const FString& val) { JsonValue = MakeShareable(new FJsonValueString(val)); return *this; }
		FJsonKeeper& operator=(const bool& val) { JsonValue = MakeShareable(new FJsonValueBoolean(val)); return *this; }
		FJsonKeeper& operator=(const int8& val) { JsonValue = MakeShareable(new FJsonValueNumber(val)); return *this; }
		FJsonKeeper& operator=(const int16& val) { JsonValue = MakeShareable(new FJsonValueNumber(val)); return *this; }
		FJsonKeeper& operator=(const int32& val) { JsonValue = MakeShareable(new FJsonValueNumber(val)); return *this; }
		FJsonKeeper& operator=(const int64& val) { JsonValue = MakeShareable(new FJsonValueNumber(val)); return *this; }
		FJsonKeeper& operator=(const uint8& val) { JsonValue = MakeShareable(new FJsonValueNumber(val)); return *this; }
		FJsonKeeper& operator=(const uint16& val) { JsonValue = MakeShareable(new FJsonValueNumber(val)); return *this; }
		FJsonKeeper& operator=(const uint32& val) { JsonValue = MakeShareable(new FJsonValueNumber(val)); return *this; }
		FJsonKeeper& operator=(const uint64& val) { JsonValue = MakeShareable(new FJsonValueNumber(val)); return *this; }
		FJsonKeeper& operator=(const float& val) { JsonValue = MakeShareable(new FJsonValueNumber(val)); return *this; }
		FJsonKeeper& operator=(const double& val) { JsonValue = MakeShareable(new FJsonValueNumber(val)); return *this; }

		~FJsonKeeper() {}
		void writeJSON(JsonWriter& writer) const override;
		bool readFromValue(const TSharedPtr<class FJsonObject>& obj) override;
		bool readFromValue(const TSharedPtr<class FJsonValue>& value) override;

		TSharedPtr<class FJsonValue> GetJsonValue() const { return JsonValue; };
	};

	void writeDatetime(FDateTime datetime, JsonWriter& writer);
	FDateTime readDatetime(const TSharedPtr<FJsonValue>& value);

	USTRUCT(BlueprintInternalUseOnly)
	struct FGameShiftRequestCommon : public FGameShiftBaseModel
	{
		GENERATED_BODY()
	};
	
	USTRUCT(BlueprintInternalUseOnly)
	struct FGameShiftResultCommon : public FGameShiftBaseModel
	{
		GENERATED_BODY()
	};
	
	USTRUCT(BlueprintType)
	struct FGameShiftPageBasedRequest : public FGameShiftRequestCommon
	{
		GENERATED_BODY()

		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 Page = 1;

		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 PerPage = 50;

		FGameShiftPageBasedRequest();

		virtual void writeJSON(JsonWriter& writer) const override;
		virtual void writeQuery(TArray<FString>& Queries) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};
	
	USTRUCT(BlueprintType)
	struct FGameShiftMetaBasedResult :public FGameShiftResultCommon
	{
		GENERATED_BODY()

	public:

		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 Page;
		
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 PerPage;
		
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 TotalPages;
		
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 TotalResults;

		FGameShiftMetaBasedResult();

		virtual void writeJSON(JsonWriter& writer) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};
	
	USTRUCT(BlueprintType)
	struct FGameShiftNullRequest :public FGameShiftRequestCommon
	{
		GENERATED_BODY()

		virtual void writeJSON(JsonWriter& writer) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};

	USTRUCT(BlueprintType)
	struct FGameShiftPageRequest : public FGameShiftPageBasedRequest
	{
		GENERATED_BODY()
	};
	
	USTRUCT(BlueprintType)
	struct FGameShiftLoginRequest : public FGameShiftRequestCommon
    {
		GENERATED_BODY()
	public:

		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FGameShiftUserLogin Login;

		FGameShiftLoginRequest();

		virtual void writeJSON(JsonWriter& Json) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
    };
	
	USTRUCT(BlueprintType)
	struct FGameShiftCreateAssetRequest : public FGameShiftRequestCommon
	{
		GENERATED_BODY()
	public:

		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FGameShiftCreateAssetDetail AssetDetail;

		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString DestinationUserReferenceID;

		FGameShiftCreateAssetRequest();
		virtual void writeJSON(JsonWriter& Json) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};
	
	USTRUCT(BlueprintType)
	struct FGameShiftAssetTransferRequest : public FGameShiftRequestCommon
	{
		GENERATED_BODY()
	public:

		//Identifies the User tranferring the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString OnBehalfOf;

		//Identifies the User receiving the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString DestinationUserReferenceID;

		//Address of the wallet receiving the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString DestinationWallet;

		FGameShiftAssetTransferRequest();

		virtual void writeJSON(JsonWriter& Json) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};
	
	USTRUCT(BlueprintType)
	struct FGameShiftLendAssetRequest : public FGameShiftRequestCommon
	{
		GENERATED_BODY()
	public:

		//Identifies the User lending the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString LenderReferenceID;

		//Identifies the User borrowing the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString BorrowerReferenceID;

		//The time the lending grant will expire
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int64 Expiration = 0;

		FGameShiftLendAssetRequest();

		virtual void writeJSON(JsonWriter& Json) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};

	USTRUCT(BlueprintType)
	struct FGameShiftCreateAssetCollectionRequest :public FGameShiftRequestCommon
	{
		GENERATED_BODY()
	public:

		//Names the Asset Collection
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Name;
		
		//Describes the Asset Collection
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Description;
			
		//URL for the Asset Collection's image
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString ImageUrl;

		FGameShiftCreateAssetCollectionRequest();

		virtual void writeJSON(JsonWriter& Json) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};
	
	USTRUCT(BlueprintType)
	struct FGameShiftUpdateAssetTemplateRequest :public FGameShiftRequestCommon
	{
		GENERATED_BODY()
	public:

		//Names the Asset created by the Template.
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Name;

		//Describes the Asset created by the Template.
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Description;

		//URL for the Asset's image
		//Example : https://solana.com/src/img/branding/solanaLogoMark.png
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString SourceImage;

		//Identifies the Asset Collection any Assets created by the Template will be assigned to
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString CollectionID;

		//Attributes for the Asset created by the Templa
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FGameShiftAssetAttribute> Attributes;

		FGameShiftUpdateAssetTemplateRequest();

		virtual void writeJSON(JsonWriter& Json) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};
	
	USTRUCT(BlueprintType)
	struct FGameShiftDestinationUserRequest : public FGameShiftRequestCommon
	{
		GENERATED_BODY()
	public:

		//Identifies the User receiving the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString DestinationUserReferenceID;

		FGameShiftDestinationUserRequest();

		virtual void writeJSON(JsonWriter& Json) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};
	
	USTRUCT(BlueprintType)
	struct FGameShiftLenderReferenceRequest : public FGameShiftRequestCommon
	{
		GENERATED_BODY()
	public:

		//Identifies the User receiving the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString LenderReferenceID;

		FGameShiftLenderReferenceRequest();

		virtual void writeJSON(JsonWriter& Json) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};

	USTRUCT(BlueprintType)
	struct FGameShiftBorrowerReferenceRequest :public FGameShiftRequestCommon
	{
		GENERATED_BODY()
	public:

		//Identifies the User receiving the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString BorrowerReferenceID;

		FGameShiftBorrowerReferenceRequest();

		virtual void writeJSON(JsonWriter& Json) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};


	USTRUCT(BlueprintType)
	struct FGameShiftCreatePaymentForAssetRequest :public FGameShiftRequestCommon
	{
		GENERATED_BODY()
	public:

		//The price of the item in cents
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 AmountCents;
			
		//The quantity of the item
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 Quantity;
			
		//The quantity of the item
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString BuyerID;

		FGameShiftCreatePaymentForAssetRequest();

		virtual void writeJSON(JsonWriter& Json) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};
	
	USTRUCT(BlueprintType)
	struct FGameShiftCreatePaymentRequest :public FGameShiftRequestCommon
	{
		GENERATED_BODY()

	public:

		//Item being purchased
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Title;
			
		//Describes the item being purchased
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Description;

		//The price of the item in cents
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 AmountCents;

		//The quantity of the item
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 Quantity;

		//The quantity of the item
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString BuyerID;

		FGameShiftCreatePaymentRequest();

		virtual void writeJSON(JsonWriter& Json) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};

	USTRUCT(BlueprintType)
	struct FGameShiftUserResult : public FGameShiftResultCommon
    {
		GENERATED_BODY()

	public:

		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FGameShiftUserAccount User;

		FGameShiftUserResult();
		virtual void writeJSON(JsonWriter& writer) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};


	USTRUCT(BlueprintType)
	struct FGameShiftUsersResult :public FGameShiftMetaBasedResult
	{
		GENERATED_BODY()
	public:
		
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FGameShiftUserAccount> Users;

		FGameShiftUsersResult();
		virtual void writeJSON(JsonWriter& writer) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};
	
	USTRUCT(BlueprintType)
	struct FGameShiftAssetResult :public FGameShiftMetaBasedResult
	{
		GENERATED_BODY()

	public:
		
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FGameShiftAsset Asset;

		FGameShiftAssetResult();
		virtual void writeJSON(JsonWriter& writer) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};
	
	USTRUCT(BlueprintType)
	struct FGameShiftAssetsResult : public FGameShiftMetaBasedResult
	{
		GENERATED_BODY()

	public:
		
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FGameShiftAsset> Assets;

		FGameShiftAssetsResult();
		virtual void writeJSON(JsonWriter& writer) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};
	

	USTRUCT(BlueprintType)
	struct FGameShiftStringResult : public FGameShiftResultCommon
	{
		GENERATED_BODY()

	public:

		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Response;

		FGameShiftStringResult();
		virtual bool readFromString(const FString& String) override;
		virtual void writeJSON(JsonWriter& writer) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};

	USTRUCT(BlueprintType)
	struct FGameShiftAssetTransferResult : public FGameShiftResultCommon
	{
		GENERATED_BODY()

	public:
		
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Url;

		FGameShiftAssetTransferResult();
		virtual bool readFromString(const FString& String) override;
		virtual void writeJSON(JsonWriter& writer) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};
	
	USTRUCT(BlueprintType)
	struct FGameShiftLendGrantResult : public FGameShiftResultCommon
	{
		GENERATED_BODY()

	public:

		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FGameShiftLendGrant LendGrant;

		FGameShiftLendGrantResult();
		virtual void writeJSON(JsonWriter& writer) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};

	USTRUCT(BlueprintType)
		struct FGameShiftLendAcceptResult : public FGameShiftResultCommon
	{
		GENERATED_BODY()

	public:

		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FGameShiftLendAccepted Acception;

		FGameShiftLendAcceptResult();
		virtual void writeJSON(JsonWriter& writer) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};

	
	USTRUCT(BlueprintType)
	struct FGameShiftAssetCollectionsResult :public FGameShiftMetaBasedResult
	{
		GENERATED_BODY()

	public:
		
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FGameShiftAssetCollection> Collections;

		FGameShiftAssetCollectionsResult();
		virtual void writeJSON(JsonWriter& writer) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};
	
	USTRUCT(BlueprintType)
	struct FGameShiftAssetCollectionResult :public FGameShiftResultCommon
	{
		GENERATED_BODY()

	public:

		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FGameShiftAssetCollection Collection;

		FGameShiftAssetCollectionResult();
		virtual void writeJSON(JsonWriter& writer) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};
	
	USTRUCT(BlueprintType)
	struct FGameShiftPaymentsResult :public FGameShiftMetaBasedResult
	{
		GENERATED_BODY()

	public:
		
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FGameShiftPayment> Payments;

		FGameShiftPaymentsResult();
		virtual void writeJSON(JsonWriter& writer) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};
	
	USTRUCT(BlueprintType)
	struct FGameShiftPaymentResult :public FGameShiftResultCommon
	{
		GENERATED_BODY()

	public:
		
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FGameShiftPayment Payment;

		FGameShiftPaymentResult();
		virtual void writeJSON(JsonWriter& writer) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};
	
	USTRUCT(BlueprintType)
	struct FGameShiftCreatedPaymentResult :public FGameShiftResultCommon
	{
		GENERATED_BODY()

	public:

		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FGameShiftCreatedPayment Payment;

		FGameShiftCreatedPaymentResult();
		virtual void writeJSON(JsonWriter& writer) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};
	
	USTRUCT(BlueprintType)
	struct FGameShiftAssetTemplatesResult : public FGameShiftMetaBasedResult
	{
		GENERATED_BODY()

	public:
		
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FGameShiftAssetTemplate> Templates;

		FGameShiftAssetTemplatesResult();
		virtual void writeJSON(JsonWriter& writer) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};
	
	USTRUCT(BlueprintType)
	struct FGameShiftAssetTemplateResult :public FGameShiftResultCommon
	{
		GENERATED_BODY()

	public:

		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FGameShiftAssetTemplate Template;

		FGameShiftAssetTemplateResult();
		virtual void writeJSON(JsonWriter& writer) const override;
		virtual bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
	};


	DECLARE_DYNAMIC_DELEGATE_OneParam(FGameShiftUserResultSignature, const FGameShiftUserResult&, Result);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGameShiftUsersResultSignature, const FGameShiftUsersResult&, Result);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGameShiftAssetsResultSignature, const FGameShiftAssetsResult&, Result);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGameShiftAssetResultSignature, const FGameShiftAssetResult&, Result);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGameShiftAssetTransferResultSignature, const FGameShiftAssetTransferResult&, Result);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGameShiftLendGrantResultSignature, const FGameShiftLendGrantResult&, Result);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGameShiftAssetCollectionsResultSignature, const FGameShiftAssetCollectionsResult&, Result);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGameShiftAssetCollectionResultSignature, const FGameShiftAssetCollectionResult&, Result);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGameShiftPaymentsResultSignature, const FGameShiftPaymentsResult&, Result);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGameShiftPaymentResultSignature, const FGameShiftPaymentResult&, Result);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGameShiftCreatedPaymentResultSignature, const FGameShiftCreatedPaymentResult&, Result);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGameShiftAssetTemplatesResultSignature, const FGameShiftAssetTemplatesResult&, Result);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGameShiftAssetTemplateResultSignature, const FGameShiftAssetTemplateResult&, Result);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGameShiftLendAcceptResultSignature, const FGameShiftLendAcceptResult&, Result);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGameShiftStringResultSignature, const FGameShiftStringResult&, Result);
