#include "GameShiftTypes.h"


FString FGameShiftFields::EmailField = TEXT("email");
FString FGameShiftFields::AddressField = TEXT("address");
FString FGameShiftFields::ReferenceIdField = TEXT("referenceId");

FString FGameShiftFields::EmptyField = TEXT("");
FString FGameShiftFields::DataField = TEXT("data");
FString FGameShiftFields::MetaField = TEXT("meta");
FString FGameShiftFields::PageField = TEXT("page");
FString FGameShiftFields::PerpageField = TEXT("perPage");
FString FGameShiftFields::TotalPageField = TEXT("totalPages");
FString FGameShiftFields::TotalResultField = TEXT("totalPages");

FString FGameShiftFields::IDField = TEXT("id");
FString FGameShiftFields::NameField = TEXT("name");
FString FGameShiftFields::DescriptionField = TEXT("description");
FString FGameShiftFields::ImageUrlField = TEXT("imageUrl");
FString FGameShiftFields::AttributesField = TEXT("attributes");
FString FGameShiftFields::CollectionIdField = TEXT("collectionId");


FString FGameShiftFields::SourceImageField = TEXT("sourceImage");
FString FGameShiftFields::AssetIDField = TEXT("assetId");
FString FGameShiftFields::OwnerIdField = TEXT("ownerId");
FString FGameShiftFields::BorrowerIdField = TEXT("borrowerId");
FString FGameShiftFields::OwnerReferenceIdField = TEXT("ownerReferenceId");
FString FGameShiftFields::BorrowerReferenceIdField = TEXT("borrowerReferenceId");
FString FGameShiftFields::LenderReferenceIdField = TEXT("lenderReferenceId");
FString FGameShiftFields::ExpirationField = TEXT("expiration");
FString FGameShiftFields::CreatedField = TEXT("created");
FString FGameShiftFields::StatusField = TEXT("status");
FString FGameShiftFields::LenderField = TEXT("lender");
FString FGameShiftFields::BorrowerField = TEXT("borrower");
FString FGameShiftFields::EnvironmentField = TEXT("environment");
FString FGameShiftFields::ProjectIdField = TEXT("projectId");
FString FGameShiftFields::CollectionField = TEXT("collection");
FString FGameShiftFields::DisplayTypeField = TEXT("displayType");
FString FGameShiftFields::TraitTypeField = TEXT("traitType");
FString FGameShiftFields::ValueField = TEXT("value");
FString FGameShiftFields::MintAddressField = TEXT("mintAddress");
FString FGameShiftFields::UrlField = TEXT("url");
FString FGameShiftFields::EscrowField = TEXT("escrow");
FString FGameShiftFields::OwnerField = TEXT("owner");

FString FGameShiftFields::EnvField = TEXT("env");
FString FGameShiftFields::ExternalIdField = TEXT("externalId");
FString FGameShiftFields::PaymentUrlField = TEXT("paymentUrl");
FString FGameShiftFields::MerchantIdField = TEXT("merchantId");
FString FGameShiftFields::ExternalMerchantIdField = TEXT("externalMerchantId");
FString FGameShiftFields::AmountCentsField = TEXT("amountCents");
FString FGameShiftFields::UserEmailField = TEXT("userEmail");
FString FGameShiftFields::UserWalletField = TEXT("userWallet");
FString FGameShiftFields::TitleField = TEXT("title");
FString FGameShiftFields::DestinationUserReferenceIDField = TEXT("destinationUserReferenceId");
FString FGameShiftFields::DetailField = TEXT("details");
FString FGameShiftFields::OnBehalfOfField = TEXT("onBehalfOf");
FString FGameShiftFields::DestinationWalletField = TEXT("destinationWallet");
FString FGameShiftFields::QuantityField = TEXT("quantity");
FString FGameShiftFields::BuyerIdField = TEXT("buyerId");
FString FGameShiftFields::UnknownStr = TEXT("Unknown");




TMap<EGameShiftAssetStatus, FString> AssetStatusToStrings = {
	{EGameShiftAssetStatus::Unprocessed ,"Unprocessed"},
	{EGameShiftAssetStatus::Processing,"Processing" },
	{EGameShiftAssetStatus::Committed,"Committed" }
};
TMap<EGameShiftPaymentStatus,FString> AssetPaymentStatusToStrings = {
	{EGameShiftPaymentStatus::Pending ,"Pending"},
	{EGameShiftPaymentStatus::Confirmed,"Confirmed" },
	{EGameShiftPaymentStatus::Completed ,"Completed"},
	{EGameShiftPaymentStatus::Failed ,"Failed"},
	{EGameShiftPaymentStatus::Expired,"Expired" }
};
TMap<EGameShiftLendGrantState, FString> AssetLendGrantStatusToStrings = {
	{EGameShiftLendGrantState::Pending ,"Pending"},
	{EGameShiftLendGrantState::Accepted ,"Accepted"},
};




TMap<FString, EGameShiftAssetStatus> StringToAssetStatus = {
	{"Unprocessed",EGameShiftAssetStatus::Unprocessed },
	{"Processing",EGameShiftAssetStatus::Processing },
	{"Committed",EGameShiftAssetStatus::Committed }
};
TMap<FString, EGameShiftPaymentStatus> StringToAssetPaymentStatus = {
	{"Pending",EGameShiftPaymentStatus::Pending },
	{"Confirmed",EGameShiftPaymentStatus::Confirmed },
	{"Completed",EGameShiftPaymentStatus::Completed },
	{"Failed",EGameShiftPaymentStatus::Failed },
	{"Expired",EGameShiftPaymentStatus::Expired }
};
TMap<FString, EGameShiftLendGrantState> StringsToAssetLendGrantStatus = {
	{"Pending",EGameShiftLendGrantState::Pending },
	{"Accepted",EGameShiftLendGrantState::Accepted },
};


EGameShiftAssetStatus FGameShiftUtility::GetAssetStatusFrom(const FString& Status)
{
	EGameShiftAssetStatus* StatusPtr = StringToAssetStatus.Find(Status);
	return (StatusPtr != nullptr) ? (*StatusPtr) : EGameShiftAssetStatus::Unknown;
}
EGameShiftPaymentStatus FGameShiftUtility::GetAssetPaymentStatusFrom(const FString& Status)
{
	EGameShiftPaymentStatus* StatusPtr = StringToAssetPaymentStatus.Find(Status);
	return (StatusPtr != nullptr) ? (*StatusPtr) : EGameShiftPaymentStatus::Unknown;
}
EGameShiftLendGrantState FGameShiftUtility::GetLendGrantStatusFrom(const FString& Status)
{
	EGameShiftLendGrantState* StatusPtr = StringsToAssetLendGrantStatus.Find(Status);
	return (StatusPtr != nullptr) ? (*StatusPtr) : EGameShiftLendGrantState::Unknown;
}


const FString& FGameShiftUtility::GetStatusString(EGameShiftAssetStatus Status)
{
	const FString* StringPtr = AssetStatusToStrings.Find(Status);
	return (StringPtr != nullptr) ? (*StringPtr) : FGameShiftFields::UnknownStr;
}
const FString& FGameShiftUtility::GetStatusString(EGameShiftPaymentStatus Status)
{
	const FString* StatusPtr = AssetPaymentStatusToStrings.Find(Status);
	return (StatusPtr != nullptr) ? (*StatusPtr) : FGameShiftFields::UnknownStr;
}
const FString& FGameShiftUtility::GetStatusString(EGameShiftLendGrantState Status)
{
	const FString* StatusPtr = AssetLendGrantStatusToStrings.Find(Status);
	return (StatusPtr != nullptr) ? (*StatusPtr) : FGameShiftFields::UnknownStr;
}


FGameShiftAssetAttribute::FGameShiftAssetAttribute()
{
	DisplayType = TEXT("");
	TraitType = TEXT("");
	Value = TEXT("");
}
void FGameShiftAssetAttribute::ToJson(JsonWriter& writerPtr, const FString& Identifier) const
{
	auto& writer = (*writerPtr);
	if (Identifier.IsEmpty())
		writer.WriteObjectStart();
	else
		writer.WriteObjectStart(Identifier);

	if (!DisplayType.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::DisplayTypeField);
		writer.WriteValue(DisplayType);
	}
	if (!TraitType.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::TraitTypeField);
		writer.WriteValue(TraitType);
	}
	if (!Value.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::ValueField);
		writer.WriteValue(Value);
	}
	writer.WriteObjectEnd();
}
bool FGameShiftAssetAttribute::FromJson(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid())
	{
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::DisplayTypeField))
			DisplayType = obj.GetStringField(FGameShiftFields::DisplayTypeField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::TraitTypeField))
			TraitType = obj.GetStringField(FGameShiftFields::TraitTypeField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::ValueField))
			Value = obj.GetStringField(FGameShiftFields::ValueField);
		return true;
	}
	return false;
}

FGameShiftAssetCollection::FGameShiftAssetCollection()
{
	ID = TEXT("");
	Name = TEXT("");
	Description = TEXT("");

	ImageUrl = TEXT("");
	MintAddress = TEXT("");

	created = 0;
}
void FGameShiftAssetCollection::ToJson(JsonWriter& writerPtr, const FString& Identifier) const
{
	auto& writer = (*writerPtr);
	if (Identifier.IsEmpty())
		writer.WriteObjectStart();
	else
		writer.WriteObjectStart(Identifier);

	if (!ID.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::IDField);
		writer.WriteValue(ID);
	}
	if (!Name.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::NameField);
		writer.WriteValue(Name);
	}
	if (!Description.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::DescriptionField);
		writer.WriteValue(Description);
	}
	if (!ImageUrl.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::ImageUrlField);
		writer.WriteValue(ImageUrl);
	}
	if (!MintAddress.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::MintAddressField);
		writer.WriteValue(MintAddress);
	}
	writer.WriteIdentifierPrefix(FGameShiftFields::CreatedField);
	writer.WriteValue(created);
	writer.WriteObjectEnd();
}
bool FGameShiftAssetCollection::FromJson(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid())
	{
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::IDField))
			ID = obj.GetStringField(FGameShiftFields::IDField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::NameField))
			Name = obj.GetStringField(FGameShiftFields::NameField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::DescriptionField))
			Description = obj.GetStringField(FGameShiftFields::DescriptionField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::ImageUrlField))
			ImageUrl = obj.GetStringField(FGameShiftFields::ImageUrlField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::MintAddressField))
			MintAddress = obj.GetStringField(FGameShiftFields::MintAddressField);
		if (obj.HasTypedField<EJson::Number>(FGameShiftFields::CreatedField))
			created = (int64)(obj.GetNumberField(FGameShiftFields::CreatedField));
		return true;
	}
	return false;
}

FGameShiftUserLogin::FGameShiftUserLogin()
{
	ReferenceID = TEXT("");
	Email = TEXT("");
}
bool FGameShiftUserLogin::FromJson(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid())
	{
		const FJsonObject& Obj = (*objPtr);
		if (Obj.HasTypedField<EJson::String>(FGameShiftFields::EmailField))
			Email = Obj.GetStringField(FGameShiftFields::EmailField);
		if (Obj.HasTypedField<EJson::String>(FGameShiftFields::ReferenceIdField))
			ReferenceID = Obj.GetStringField(FGameShiftFields::ReferenceIdField);
		return !Email.IsEmpty() && !ReferenceID.IsEmpty();
	}
	return false;
}
void FGameShiftUserLogin::ToJson(JsonWriter& writerPtr, const FString& Identifier) const
{
	auto& writer = (*writerPtr);
	if (Identifier.IsEmpty())
		writer.WriteObjectStart();
	else
		writer.WriteObjectStart(Identifier);

	if (!Email.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::EmailField);
		writer.WriteValue(Email);
	}
	if (!ReferenceID.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::ReferenceIdField);
		writer.WriteValue(ReferenceID);
	}
	writer.WriteObjectEnd();
}

FGameShiftUserAccount::FGameShiftUserAccount()
{
	Address = TEXT("");
	ReferenceID = TEXT("");
	Email = TEXT("");
}
bool FGameShiftUserAccount::FromJson(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid())
	{
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::AddressField))
			Address = obj.GetStringField(FGameShiftFields::AddressField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::ReferenceIdField))
			ReferenceID = obj.GetStringField(FGameShiftFields::ReferenceIdField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::EmailField))
			Email = obj.GetStringField(FGameShiftFields::EmailField);
		return true;
	}
	return false;
}
void FGameShiftUserAccount::ToJson(JsonWriter& writerPtr, const FString& Identifier) const
{
	auto& writer = (*writerPtr);
	if (Identifier.IsEmpty())
		writer.WriteObjectStart();
	else
		writer.WriteObjectStart(Identifier);

	if (!Email.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::EmailField);
		writer.WriteValue(Email);
	}
	if (!Address.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::AddressField);
		writer.WriteValue(Address);
	}
	if (!ReferenceID.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::ReferenceIdField);
		writer.WriteValue(ReferenceID);
	}
	writer.WriteObjectEnd();
}

FGameShiftAsset::FGameShiftAsset()
{
	ID = TEXT("");
	Name = TEXT("");
	ImageUrl = TEXT("");
	MintAddress = TEXT("");
	Owner = FGameShiftUserAccount();
	Attributes.Reset();
	Collection = FGameShiftAssetCollection();
	Created = 0;
	Status = EGameShiftAssetStatus::Unknown;
	bEscrow = false;
}
bool FGameShiftAsset::FromJson(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid())
	{
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::IDField))
			ID = obj.GetStringField(FGameShiftFields::IDField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::NameField))
			Name = obj.GetStringField(FGameShiftFields::NameField);
		if (obj.HasTypedField<EJson::Number>(FGameShiftFields::CreatedField))
			Created = (int64)(obj.GetNumberField(FGameShiftFields::CreatedField));

		Attributes.Reset();
		if (obj.HasTypedField<EJson::Array>(FGameShiftFields::AttributesField))
		{
			const TArray<TSharedPtr<FJsonValue>>& DataArrayJson = obj.GetArrayField(FGameShiftFields::AttributesField);
			for (auto It = DataArrayJson.CreateConstIterator(); It; ++It)
			{
				const TSharedPtr<FJsonValue>& DataJsonPtr = *It;
				if (DataJsonPtr.IsValid())
				{
					FGameShiftAssetAttribute Attribute = FGameShiftAssetAttribute();
					Attribute.FromJson(DataJsonPtr->AsObject());
					Attributes.Add(Attribute);
				}
			}
		}

		if (obj.HasTypedField<EJson::Number>(FGameShiftFields::CollectionField))
		{
			FGameShiftAssetCollection AssetCollection = FGameShiftAssetCollection();
			AssetCollection.FromJson(obj.GetObjectField(FGameShiftFields::CollectionField));
			Collection = AssetCollection;
		}
		if (obj.HasTypedField<EJson::Boolean>(FGameShiftFields::EscrowField))
			bEscrow = obj.GetBoolField(FGameShiftFields::EscrowField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::MintAddressField))
			MintAddress = obj.GetStringField(FGameShiftFields::MintAddressField);
		if (obj.HasTypedField<EJson::Object>(FGameShiftFields::OwnerField))
		{
			FGameShiftUserAccount UserAccount = FGameShiftUserAccount();
			UserAccount.FromJson(obj.GetObjectField(FGameShiftFields::OwnerField));
			Owner = UserAccount;
		}
		return true;
	}
	return false;
}

FGameShiftAssetTemplate::FGameShiftAssetTemplate()
{
	ID = TEXT("");
	Name = TEXT("");
	Description = TEXT("");
	SourceImage = TEXT("");
	Collection = FGameShiftAssetCollection();
	Attributes.Reset();
	Created = TEXT("");
}
bool FGameShiftAssetTemplate::FromJson(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid())
	{
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::IDField))
			ID = obj.GetStringField(FGameShiftFields::IDField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::NameField))
			Name = obj.GetStringField(FGameShiftFields::NameField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::DescriptionField))
			Description = obj.GetStringField(FGameShiftFields::DescriptionField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::SourceImageField))
			SourceImage = obj.GetStringField(FGameShiftFields::SourceImageField);
		if (obj.HasTypedField<EJson::Object>(FGameShiftFields::CollectionField))
		{
			FGameShiftAssetCollection AssetCollection = FGameShiftAssetCollection();
			AssetCollection.FromJson(obj.GetObjectField(FGameShiftFields::CollectionField));
			Collection = AssetCollection;
		}

		Attributes.Reset();
		if (obj.HasTypedField<EJson::Array>(FGameShiftFields::AttributesField))
		{
			Attributes.Reset();
			const TArray<TSharedPtr<FJsonValue>>& AttributeArray = obj.GetArrayField(FGameShiftFields::AttributesField);
			for (auto It = AttributeArray.CreateConstIterator(); It; ++It)
			{
				FGameShiftAssetAttribute Attribute = FGameShiftAssetAttribute();
				Attribute.FromJson((*It)->AsObject());
				Attributes.Add(Attribute);
			}
		}
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::CreatedField))
			Created = obj.GetStringField(FGameShiftFields::CreatedField);
		return true;
	}
	return false;
}

FGameShiftPayment::FGameShiftPayment()
{
	ID = TEXT("");
	Env = TEXT("");
	ExternalID = TEXT("");
	Status = EGameShiftPaymentStatus::Unknown;
	PaymentUrl = TEXT("");
	MerchantID = TEXT("");
	ExternalMerchantID = TEXT("");
	AmountCents = 0;
	UserEmail = TEXT("");
	UserWallet = TEXT("");
	Description = TEXT("");
	Title = TEXT("");
	Description = TEXT("");
}
bool FGameShiftPayment::FromJson(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid())
	{
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::IDField))
			ID = obj.GetStringField(FGameShiftFields::IDField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::EnvField))
			Env = obj.GetStringField(FGameShiftFields::EnvField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::ExternalIdField))
			ExternalID = obj.GetStringField(FGameShiftFields::ExternalIdField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::StatusField))
		{
			FString StatusStr = obj.GetStringField(FGameShiftFields::StatusField);
			Status = FGameShiftUtility::GetAssetPaymentStatusFrom(StatusStr);
		}
		if (obj.HasTypedField<EJson::Object>(FGameShiftFields::PaymentUrlField))
			PaymentUrl = obj.GetStringField(FGameShiftFields::PaymentUrlField);
		if (obj.HasTypedField<EJson::Array>(FGameShiftFields::MerchantIdField))
			MerchantID = obj.GetStringField(FGameShiftFields::MerchantIdField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::ExternalMerchantIdField))
			ExternalMerchantID = obj.GetStringField(FGameShiftFields::ExternalMerchantIdField);
		if (obj.HasTypedField<EJson::Number>(FGameShiftFields::AmountCentsField))
			AmountCents = obj.GetIntegerField(FGameShiftFields::AmountCentsField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::UserEmailField))
			UserEmail = obj.GetStringField(FGameShiftFields::UserEmailField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::UserWalletField))
			UserWallet = obj.GetStringField(FGameShiftFields::UserWalletField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::TitleField))
			Title = obj.GetStringField(FGameShiftFields::TitleField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::DescriptionField))
			Description = obj.GetStringField(FGameShiftFields::DescriptionField);
		return true;
	}
	return false;
}

FGameShiftCreatedPayment::FGameShiftCreatedPayment()
{
	Url = TEXT("");
	ID = TEXT("");
}
bool FGameShiftCreatedPayment::FromJson(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid())
	{
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::IDField))
			ID = obj.GetStringField(FGameShiftFields::IDField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::UrlField))
			Url = obj.GetStringField(FGameShiftFields::UrlField);
		return true;
	}
	return false;
}
void FGameShiftCreatedPayment::ToJson(JsonWriter& writerPtr, const FString& Identifier) const
{
	auto& writer = (*writerPtr);
	if (Identifier.IsEmpty())
		writer.WriteObjectStart();
	else
		writer.WriteObjectStart(Identifier);

	if (!ID.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::IDField);
		writer.WriteValue(ID);
	}
	if (!Url.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::UrlField);
		writer.WriteValue(Url);
	}
	writer.WriteObjectEnd();
}

FGameShiftLendGrant::FGameShiftLendGrant()
{
	ID = TEXT("");
	AssetID = TEXT("");
	OwnerReferenceID = TEXT("");
	BorrowerReferenceID = TEXT("");
	Expiration = TEXT("");
	Created = TEXT("");
	Status = EGameShiftLendGrantState::Unknown;
	Lender = FGameShiftUserAccount();
	Borrower = FGameShiftUserAccount();
	Environment = TEXT("");
	ProjectID = TEXT("");
}
bool FGameShiftLendGrant::FromJson(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid())
	{
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::IDField))
			ID = obj.GetStringField(FGameShiftFields::IDField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::AssetIDField))
			AssetID = obj.GetStringField(FGameShiftFields::AssetIDField);

		if (obj.HasTypedField<EJson::String>(FGameShiftFields::OwnerReferenceIdField))
			OwnerReferenceID = obj.GetStringField(FGameShiftFields::OwnerReferenceIdField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::BorrowerReferenceIdField))
			BorrowerReferenceID = obj.GetStringField(FGameShiftFields::BorrowerReferenceIdField);
		
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::ExpirationField))
			Expiration = obj.GetStringField(FGameShiftFields::ExpirationField);
		
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::CreatedField))
			Created = obj.GetStringField(FGameShiftFields::CreatedField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::StatusField))
		{
			FString StatusStr = obj.GetStringField(FGameShiftFields::StatusField);
			Status = FGameShiftUtility::GetLendGrantStatusFrom(StatusStr);
		}
		if (obj.HasTypedField<EJson::Object>(FGameShiftFields::LenderField))
		{
			FGameShiftUserAccount Account = FGameShiftUserAccount();
			Account.FromJson(obj.GetObjectField(FGameShiftFields::LenderField));
			Lender = Account;
		}
		if (obj.HasTypedField<EJson::Object>(FGameShiftFields::BorrowerField))
		{
			FGameShiftUserAccount Account = FGameShiftUserAccount();
			Account.FromJson(obj.GetObjectField(FGameShiftFields::BorrowerField));
			Borrower = Account;
		}

		if (obj.HasTypedField<EJson::String>(FGameShiftFields::EnvironmentField))
			Environment = obj.GetStringField(FGameShiftFields::EnvironmentField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::ProjectIdField))
			ProjectID = obj.GetStringField(FGameShiftFields::ProjectIdField);
		return true;
	}
	return false;
}

FGameShiftLendAccepted::FGameShiftLendAccepted()
{
	ID = TEXT("");
	AssetID = TEXT("");
	OwnerID = TEXT("");
	BorrowerID = TEXT("");
	Expiration = TEXT("");
	Created = TEXT("");
	Status = EGameShiftLendGrantState::Unknown;
	Environment = TEXT("");
	ProjectID = TEXT("");
}
bool FGameShiftLendAccepted::FromJson(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid())
	{
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::IDField))
			ID = obj.GetStringField(FGameShiftFields::IDField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::AssetIDField))
			AssetID = obj.GetStringField(FGameShiftFields::AssetIDField);

		if (obj.HasTypedField<EJson::String>(FGameShiftFields::OwnerIdField))
			OwnerID = obj.GetStringField(FGameShiftFields::OwnerIdField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::BorrowerIdField))
			BorrowerID = obj.GetStringField(FGameShiftFields::BorrowerIdField);

		if (obj.HasTypedField<EJson::String>(FGameShiftFields::ExpirationField))
			Expiration = obj.GetStringField(FGameShiftFields::ExpirationField);

		if (obj.HasTypedField<EJson::String>(FGameShiftFields::CreatedField))
			Created = obj.GetStringField(FGameShiftFields::CreatedField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::StatusField))
		{
			FString StatusStr = obj.GetStringField(FGameShiftFields::StatusField);
			Status = FGameShiftUtility::GetLendGrantStatusFrom(StatusStr);
		}
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::EnvironmentField))
			Environment = obj.GetStringField(FGameShiftFields::EnvironmentField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::ProjectIdField))
			ProjectID = obj.GetStringField(FGameShiftFields::ProjectIdField);
		return true;
	}
	return false;
}



FGameShiftCreateAssetDetail::FGameShiftCreateAssetDetail()
{
	Attributes.Reset();
	CollectionID = TEXT("");
	Name = TEXT("");
	Description = TEXT("");
	ImageUrl = TEXT("");
}
void FGameShiftCreateAssetDetail::ToJson(JsonWriter& writerPtr, const FString& Identifier) const
{
	auto& writer = (*writerPtr);
	if (Identifier.IsEmpty())
		writer.WriteObjectStart();
	else
		writer.WriteObjectStart(Identifier);

	writer.WriteArrayStart(FGameShiftFields::AttributesField);
	for (auto It = Attributes.CreateConstIterator(); It; ++It)
	{
		const FGameShiftAssetAttribute& Attibute = *It;
		Attibute.ToJson(writerPtr);
	}
	writer.WriteArrayEnd();

	writer.WriteIdentifierPrefix(FGameShiftFields::CollectionIdField);
	writer.WriteValue(CollectionID);

	writer.WriteIdentifierPrefix(FGameShiftFields::DescriptionField);
	writer.WriteValue(Description);

	writer.WriteIdentifierPrefix(FGameShiftFields::ImageUrlField);
	writer.WriteValue(ImageUrl);

	writer.WriteIdentifierPrefix(FGameShiftFields::NameField);
	writer.WriteValue(Name);

	writer.WriteObjectEnd();
}
bool FGameShiftCreateAssetDetail::FromJson(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid())
	{
		const FJsonObject& obj = (*objPtr);
		Attributes.Reset();
		if (obj.HasTypedField<EJson::Array>(FGameShiftFields::AttributesField))
		{
			const TArray<TSharedPtr<FJsonValue>>& DataArrayJson = obj.GetArrayField(FGameShiftFields::AttributesField);
			for (auto It = DataArrayJson.CreateConstIterator(); It; ++It)
			{
				const TSharedPtr<FJsonValue>& DataJsonPtr = *It;
				if (DataJsonPtr.IsValid())
				{
					FGameShiftAssetAttribute Attribute = FGameShiftAssetAttribute();
					Attribute.FromJson(DataJsonPtr->AsObject());
					Attributes.Add(Attribute);
				}
			}
		}
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::CollectionIdField))
			CollectionID = obj.GetStringField(FGameShiftFields::CollectionIdField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::DescriptionField))
			Description = obj.GetStringField(FGameShiftFields::DescriptionField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::ImageUrlField))
			ImageUrl = obj.GetStringField(FGameShiftFields::ImageUrlField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::NameField))
			Name = obj.GetStringField(FGameShiftFields::NameField);
		return true;
	}
	return false;
}
