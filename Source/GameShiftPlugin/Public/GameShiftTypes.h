#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonReader.h"
#include "GameShiftTypes.generated.h"


struct FGameShiftFields
{
	static FString UnknownStr;
	static FString EmptyField;
	static FString EmailField;
	static FString AddressField;
	static FString ReferenceIdField;
	static FString DataField;
	static FString MetaField;
	static FString PageField;
	static FString PerpageField;
	static FString TotalPageField;
	static FString TotalResultField;

	static FString IDField;
	static FString NameField;
	static FString DescriptionField;
	static FString ImageUrlField;
	static FString AttributesField;
	static FString CollectionIdField;

	static FString SourceImageField;
	static FString AssetIDField;
	static FString OwnerReferenceIdField;
	static FString BorrowerReferenceIdField;
	static FString OwnerIdField;
	static FString BorrowerIdField;
	static FString LenderReferenceIdField;
	static FString ExpirationField;
	static FString CreatedField;
	static FString StatusField;
	static FString LenderField;
	static FString BorrowerField;
	static FString EnvironmentField;
	static FString ProjectIdField;
	static FString CollectionField;
	static FString DisplayTypeField;
	static FString TraitTypeField;
	static FString ValueField;
	static FString MintAddressField;
	static FString UrlField;
	static FString EscrowField;
	static FString OwnerField;

	static FString EnvField;
	static FString ExternalIdField;
	static FString PaymentUrlField;
	static FString MerchantIdField;
	static FString ExternalMerchantIdField;
	static FString AmountCentsField;
	static FString UserEmailField;
	static FString UserWalletField;
	static FString TitleField;
	static FString DetailField;
	static FString DestinationUserReferenceIDField;
	static FString DestinationWalletField;
	static FString OnBehalfOfField;
	static FString QuantityField;
	static FString BuyerIdField;
};


typedef TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter;
typedef TSharedRef<TJsonReader<TCHAR>> JsonReader;

	USTRUCT(BlueprintInternalUseOnly)
	struct FGameShiftDataInterface
	{
		GENERATED_BODY()

		virtual ~FGameShiftDataInterface() {}
		virtual bool FromJson(const TSharedPtr<FJsonObject>& obj) { return false; }
		virtual void ToJson(JsonWriter& writer, const FString& Identifier = FGameShiftFields::EmptyField) const {}
	};

	UENUM(BlueprintType)
	enum class EGameShiftAssetStatus : uint8
	{
		Unknown,
		Unprocessed,
		Processing,
		Committed
	};
	
	UENUM(BlueprintType)
	enum class EGameShiftPaymentStatus : uint8
	{
		Unknown,
		Pending,
		Confirmed,
		Completed,
		Failed,
		Expired
	};
	
	UENUM(BlueprintType)
	enum class EGameShiftLendGrantState : uint8
	{
		Unknown,
		Pending,
		Accepted
	};

	struct FGameShiftUtility
	{
		static EGameShiftAssetStatus GetAssetStatusFrom(const FString& Status);
		static EGameShiftPaymentStatus GetAssetPaymentStatusFrom(const FString& Status);
		static EGameShiftLendGrantState GetLendGrantStatusFrom(const FString& Status);

		static const FString& GetStatusString(EGameShiftAssetStatus Status);
		static const FString& GetStatusString(EGameShiftPaymentStatus Status);
		static const FString& GetStatusString(EGameShiftLendGrantState Status);
	};

	USTRUCT(BlueprintType)
	struct FGameShiftAssetAttribute : public FGameShiftDataInterface
	{
		GENERATED_BODY()

		//An optional field that represents how the trait name would be displayed to the user
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString DisplayType;

		//The name of the trait
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString TraitType;

		//The value of the trait
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Value;

		FGameShiftAssetAttribute();
		virtual void ToJson(JsonWriter& writer, const FString& Identifier = FGameShiftFields::EmptyField) const override;
		virtual bool FromJson(const TSharedPtr<FJsonObject>& obj) override;

	};
	
	USTRUCT(BlueprintType)
	struct FGameShiftAssetCollection : public FGameShiftDataInterface
	{
		GENERATED_BODY()

		//The id of the collection. This is not an on-chain address, but instead an ID internal to GameShift
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString ID;

		//The name given to the collection
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Name;

		//The description given to the collection
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Description;

		//The url of the image used to represent the collection
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString ImageUrl;

		//The mint address of the collection on-chain
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString MintAddress;

		//Timestamp of collection creation
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int64 created;

		FGameShiftAssetCollection();

		virtual void ToJson(JsonWriter& writer, const FString& Identifier = FGameShiftFields::EmptyField) const override;
		virtual bool FromJson(const TSharedPtr<FJsonObject>& obj) override;
	};
	
	USTRUCT(BlueprintType)
	struct FGameShiftUserLogin : public FGameShiftDataInterface
	{
		GENERATED_BODY()

		//The reference id of the user
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString ReferenceID;

		//The email of the user
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Email;

		FGameShiftUserLogin();

		virtual bool FromJson(const TSharedPtr<FJsonObject>& obj) override;
		virtual void ToJson(JsonWriter& writer, const FString& Identifier = FGameShiftFields::EmptyField) const override;
	};

	USTRUCT(BlueprintType)
	struct FGameShiftUserAccount : public FGameShiftDataInterface
	{
		GENERATED_BODY()

	public:
		
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Address;

		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString ReferenceID;

		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Email;

		FGameShiftUserAccount();

		virtual bool FromJson(const TSharedPtr<FJsonObject>& obj) override;
		virtual void ToJson(JsonWriter& writer, const FString& Identifier = FGameShiftFields::EmptyField) const override;
	};

	USTRUCT(BlueprintType)
	struct FGameShiftCreateAssetDetail : public FGameShiftDataInterface
	{
		GENERATED_BODY()

		//The attributes of the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FGameShiftAssetAttribute> Attributes;

		//Add the Asset to an existing collection
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString CollectionID;

		//The name of the Asset.Max length : 32 chars
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Name;

		//A description for the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Description;

		//A url to the image underlying the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString ImageUrl;

		FGameShiftCreateAssetDetail();

		virtual void ToJson(JsonWriter& writer, const FString& Identifier = FGameShiftFields::EmptyField) const override;
		virtual bool FromJson(const TSharedPtr<FJsonObject>& obj) override;
	};

	USTRUCT(BlueprintType)
	struct FGameShiftAsset : public FGameShiftDataInterface
	{
		GENERATED_BODY()

		//The ID of the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString ID;

		//The name of the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Name;

		//The URI for the image representing the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString ImageUrl;

		//The address of the Asset on the blockchain
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString MintAddress;

		//The current owner of the Asset.
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FGameShiftUserAccount Owner;

		//The attributes of the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FGameShiftAssetAttribute> Attributes;

		//The collection the Asset belongs to
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FGameShiftAssetCollection Collection;

		//The date the Asset was created
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int64 Created;

		//The current status of the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		EGameShiftAssetStatus Status;

		//If the asset is in escrow or not
		bool bEscrow;

		FGameShiftAsset();

		virtual bool FromJson(const TSharedPtr<FJsonObject>& obj) override;
	};

	USTRUCT(BlueprintType)
	struct FGameShiftAssetTemplate : public FGameShiftDataInterface
	{
		GENERATED_BODY()

		//The ID of the Asset Template
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString ID;

		//When an Asset is created from this Asset Template, this name will be used
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Name;

		//When an Asset is created from this Asset Template, this description will be used
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Description;

		//When an Asset is created from this Asset Template, this image will be used
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString SourceImage;

		//When an Asset is created from this Asset Template, it will be assigned to this Collection
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FGameShiftAssetCollection Collection;

		//When an Asset is created from this Asset Template, these attributes will be added to the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FGameShiftAssetAttribute> Attributes;

		//Timestamp of asset creation
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Created;

		FGameShiftAssetTemplate();
		virtual bool FromJson(const TSharedPtr<FJsonObject>& obj) override;
	};

	USTRUCT(BlueprintType)
	struct FGameShiftCreatedPayment : public FGameShiftDataInterface
	{
		GENERATED_BODY()

		//A URL the User must visit to complete the payment
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Url;

		//An id used to reference the payment
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString ID;

		FGameShiftCreatedPayment();

		virtual void ToJson(JsonWriter& writer, const FString& Identifier = FGameShiftFields::EmptyField) const override;
		virtual bool FromJson(const TSharedPtr<FJsonObject>& obj) override;
	};

	USTRUCT(BlueprintType)
	struct FGameShiftPayment : public FGameShiftDataInterface
	{
		GENERATED_BODY()

		//The ID of the payment
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString ID;

		//Environment the payment initiated on
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Env;

		//External ID of the payment
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString ExternalID;

		//Status of the payment
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		EGameShiftPaymentStatus	Status;

		//The url for the payment checkout
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString PaymentUrl;

		//The url for the payment checkout
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString MerchantID;

		//The id of the merchant charging the payment in the provider
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString ExternalMerchantID;

		//The payment amount in cents
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 AmountCents;

		//The email of the user who initiated the payment
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString UserEmail;

		//The wallet address of the user who initiated the payment
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString UserWallet;

		//The item being purchased
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Title;

		//The description of the item being purchased
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Description;

		FGameShiftPayment();

		virtual bool FromJson(const TSharedPtr<FJsonObject>& obj) override;
	};

	USTRUCT(BlueprintType)
	struct FGameShiftLendGrant : public FGameShiftDataInterface
	{
		GENERATED_BODY()

		//The unique ID of the LendingGrant entry
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString ID;

		//The ID of the Asset being borrowed
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString AssetID;

		//The reference ID of the owner of the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString OwnerReferenceID;

		//The reference ID of the borrower of the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString BorrowerReferenceID;

		//The expiration date and time of the borrowing period
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Expiration;

		//The date and time when the borrow entry was created
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Created;

		//The current status of the LendingGrant entry
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		EGameShiftLendGrantState Status;

		//The current owner of the Asset, if available
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FGameShiftUserAccount Lender;

		//The current owner of the Asset, if available
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FGameShiftUserAccount Borrower;

		//The current environment of the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Environment;

		//The lending grant's project ID
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString ProjectID;

		FGameShiftLendGrant();

		virtual bool FromJson(const TSharedPtr<FJsonObject>& obj) override;
	};

	USTRUCT(BlueprintType)
	struct FGameShiftLendAccepted : public FGameShiftDataInterface
	{
		GENERATED_BODY()

			//The unique ID of the LendingGrant entry
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString ID;

		//The ID of the Asset being borrowed
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString AssetID;

		//The reference ID of the owner of the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString OwnerID;

		//The reference ID of the borrower of the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString BorrowerID;

		//The expiration date and time of the borrowing period
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Expiration;

		//The date and time when the borrow entry was created
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Created;

		//The current status of the LendingGrant entry
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		EGameShiftLendGrantState Status;

		//The current environment of the Asset
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString Environment;

		//The lending grant's project ID
		UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString ProjectID;

		FGameShiftLendAccepted();

		virtual bool FromJson(const TSharedPtr<FJsonObject>& obj) override;
	};
