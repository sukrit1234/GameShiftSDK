//////////////////////////////////////////////////////
// Copyright (C) Microsoft. 2018. All rights reserved.
//////////////////////////////////////////////////////


#include "GameShiftBaseModel.h"
#include "Templates/SharedPointer.h"


FString FGameShiftBaseModel::toJSONString() const
{
    FString JsonOutString;
    JsonWriter Json = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR> >::Create(&JsonOutString);
    writeJSON(Json);
    Json->Close();
    return JsonOutString;
}
FString FGameShiftBaseModel::toQueryString() const
{
	TArray<FString> Queries;
	Queries.Reserve(1024);
	writeQuery(Queries);
	return FString::Join(Queries, TEXT("&"));
}

void FJsonKeeper::writeJSON(JsonWriter& writer) const
{
	switch (JsonValue->Type)
	{
	case EJson::None:
	{
		break;
	}
	case EJson::Array:
	{
		writer->WriteArrayStart();
		for (auto Elem : JsonValue->AsArray())
		{
			FJsonKeeper(Elem).writeJSON(writer);
		}
		writer->WriteArrayEnd();
		break;
	}
	case EJson::Boolean:
	{
		writer->WriteValue(JsonValue->AsBool());
		break;
	}
	case EJson::Number:
	{
		writer->WriteValue(JsonValue->AsNumber());
		break;
	}
	case EJson::Object:
	{
		writer->WriteObjectStart();
		for (auto Elem : JsonValue->AsObject()->Values)
		{
			writer->WriteIdentifierPrefix(Elem.Key);
			FJsonKeeper(Elem.Value).writeJSON(writer);
		}
		writer->WriteObjectEnd();
		break;
	}
	case EJson::String:
	{
		writer->WriteValue(JsonValue->AsString());
		break;
	}
	case EJson::Null:
	{
		writer->WriteNull();
		break;
	}
	default:
	{
		break;
	}
	}
}
bool FJsonKeeper::readFromValue(const TSharedPtr<FJsonObject>& obj)
{
	return false;
}
bool FJsonKeeper::readFromValue(const TSharedPtr<FJsonValue>& value)
{
	if (value.IsValid())
	{
		JsonValue = value.ToSharedRef();
	}
	return true;
}
void writeDatetime(FDateTime datetime, JsonWriter& writer)
{
	writer->WriteValue(datetime.ToIso8601());
}
FDateTime readDatetime(const TSharedPtr<FJsonValue>& value)
{
	FDateTime DateTimeOut;
	FString DateString = value->AsString();
	if (!FDateTime::ParseIso8601(*DateString, DateTimeOut))
	{
		UE_LOG(LogGameShift, Error, TEXT("readDatetime - Unable to import FDateTime from Iso8601 String. If you see FDateTime::MinValue (or FDateTime(0)), investigate the value being passed in and handle possible mis-parsing of ParseIso8601."));
		DateTimeOut = FDateTime::MinValue();
	}

	return DateTimeOut;
}



FGameShiftLoginRequest::FGameShiftLoginRequest()
{
	Login = FGameShiftUserLogin();
}
void FGameShiftLoginRequest::writeJSON(JsonWriter& writerPtr) const
{
	Login.ToJson(writerPtr);
}
bool FGameShiftLoginRequest::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	return Login.FromJson(objPtr);
}

FGameShiftUserResult::FGameShiftUserResult()
{
	User = FGameShiftUserAccount();
}
void FGameShiftUserResult::writeJSON(JsonWriter& writerPtr) const
{
	User.ToJson(writerPtr);
}
bool FGameShiftUserResult::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	return User.FromJson(objPtr);
}

FGameShiftMetaBasedResult::FGameShiftMetaBasedResult()
{
	Page = 0;
	PerPage = 0;
	TotalPages = 0;
	TotalResults = 0;
}
void FGameShiftMetaBasedResult::writeJSON(JsonWriter& writerPtr) const
{
	auto& writer = (*writerPtr);
	writer.WriteObjectStart(FGameShiftFields::MetaField);
	
	writer.WriteIdentifierPrefix(FGameShiftFields::PageField);
	writer.WriteValue(Page);

	writer.WriteIdentifierPrefix(FGameShiftFields::PerpageField);
	writer.WriteValue(PerPage);

	writer.WriteIdentifierPrefix(FGameShiftFields::TotalPageField);
	writer.WriteValue(TotalPages);

	writer.WriteIdentifierPrefix(FGameShiftFields::TotalResultField);
	writer.WriteValue(TotalResults);

	writer.WriteObjectEnd();
}
bool FGameShiftMetaBasedResult::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	bool HasSucceeded = true;
	if (objPtr.IsValid()) {
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::Object>(FGameShiftFields::MetaField)) {
			const TSharedPtr<FJsonObject>& MetaObjectJsonPtr = obj.GetObjectField(FGameShiftFields::MetaField);
			if (MetaObjectJsonPtr.IsValid()) {
				const FJsonObject& MetaObjectJson = (*MetaObjectJsonPtr);
				if (MetaObjectJson.HasTypedField<EJson::Number>(FGameShiftFields::PageField))
					Page = MetaObjectJson.GetIntegerField(FGameShiftFields::PageField);
				if (MetaObjectJson.HasTypedField<EJson::Number>(FGameShiftFields::PerpageField))
					PerPage = MetaObjectJson.GetIntegerField(FGameShiftFields::PerpageField);
				if (MetaObjectJson.HasTypedField<EJson::Number>(FGameShiftFields::TotalPageField))
					TotalPages = MetaObjectJson.GetIntegerField(FGameShiftFields::TotalPageField);
				if (MetaObjectJson.HasTypedField<EJson::Number>(FGameShiftFields::TotalResultField))
					TotalResults = MetaObjectJson.GetIntegerField(FGameShiftFields::TotalResultField);
				return true;
			}
		}
	}
	return false;
}

FGameShiftPageBasedRequest::FGameShiftPageBasedRequest()
{
	Page = 1;
	PerPage = 50;
}
void FGameShiftPageBasedRequest::writeQuery(TArray<FString>& Queries) const
{
	Queries.Add(FString::Printf(TEXT("%s=%d"), *FGameShiftFields::PageField, Page));
	Queries.Add(FString::Printf(TEXT("%s=%d"), *FGameShiftFields::PerpageField, PerPage));
}
void FGameShiftPageBasedRequest::writeJSON(JsonWriter& writerPtr) const
{
	auto& writer = (*writerPtr);
	writer.WriteObjectStart();

	writer.WriteIdentifierPrefix(FGameShiftFields::PageField);
	writer.WriteValue((Page < 1) ? 1 : Page);

	writer.WriteIdentifierPrefix(FGameShiftFields::PerpageField);
	writer.WriteValue((PerPage < 1) ? 1 : PerPage);

	writer.WriteObjectEnd();
}
bool FGameShiftPageBasedRequest::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid()) {
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::Number>(FGameShiftFields::PageField))
			Page = obj.GetIntegerField(FGameShiftFields::PageField);
		if (obj.HasTypedField<EJson::Number>(FGameShiftFields::PerpageField))
			PerPage = obj.GetIntegerField(FGameShiftFields::PerpageField);
		return true;
	}
	return false;
}

FGameShiftCreateAssetRequest::FGameShiftCreateAssetRequest()
{
	AssetDetail = FGameShiftCreateAssetDetail();
	DestinationUserReferenceID = TEXT("");
}
void FGameShiftCreateAssetRequest::writeJSON(JsonWriter& writerPtr) const
{
	auto& writer = (*writerPtr);
	writer.WriteObjectStart();
	AssetDetail.ToJson(writerPtr, FGameShiftFields::DetailField);
	writer.WriteIdentifierPrefix(FGameShiftFields::DestinationUserReferenceIDField);
	writer.WriteValue(DestinationUserReferenceID);
	writer.WriteObjectEnd();
}
bool FGameShiftCreateAssetRequest::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid()) {
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::Object>(FGameShiftFields::DetailField))
			AssetDetail.FromJson(obj.GetObjectField(FGameShiftFields::DetailField));
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::DestinationUserReferenceIDField))
			DestinationUserReferenceID = obj.GetStringField(FGameShiftFields::DestinationUserReferenceIDField);
		return true;
	}
	return false;
}

FGameShiftAssetTransferRequest::FGameShiftAssetTransferRequest()
{
	OnBehalfOf = TEXT("");
	DestinationUserReferenceID = TEXT("");
	DestinationWallet = TEXT("");
}
void FGameShiftAssetTransferRequest::writeJSON(JsonWriter& writerPtr) const
{
	auto& writer = (*writerPtr);
	writer.WriteObjectStart();

	writer.WriteIdentifierPrefix(FGameShiftFields::OnBehalfOfField);
	writer.WriteValue(OnBehalfOf);

	if (!DestinationUserReferenceID.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::DestinationUserReferenceIDField);
		writer.WriteValue(DestinationUserReferenceID);
	}

	if (!DestinationWallet.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::DestinationWalletField);
		writer.WriteValue(DestinationWallet);
	}

	writer.WriteObjectEnd();
}
bool FGameShiftAssetTransferRequest::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid()) {
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::OnBehalfOfField))
			OnBehalfOf = obj.GetStringField(FGameShiftFields::OnBehalfOfField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::DestinationUserReferenceIDField))
			DestinationUserReferenceID = obj.GetStringField(FGameShiftFields::DestinationUserReferenceIDField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::DestinationWalletField))
			DestinationWallet = obj.GetStringField(FGameShiftFields::DestinationWalletField);
		return true;
	}
	return false;
}

FGameShiftLendAssetRequest::FGameShiftLendAssetRequest()
{
	LenderReferenceID = TEXT("");
	BorrowerReferenceID = TEXT("");
	Expiration = 0;
}
void FGameShiftLendAssetRequest::writeJSON(JsonWriter& writerPtr) const
{
	auto& writer = (*writerPtr);
	writer.WriteObjectStart();

	writer.WriteIdentifierPrefix(FGameShiftFields::LenderReferenceIdField);
	writer.WriteValue(LenderReferenceID);

	writer.WriteIdentifierPrefix(FGameShiftFields::BorrowerReferenceIdField);
	writer.WriteValue(BorrowerReferenceID);

	if (Expiration > 0)
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::ExpirationField);
		writer.WriteValue(Expiration);
	}
	writer.WriteObjectEnd();
}
bool FGameShiftLendAssetRequest::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid()) {
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::LenderReferenceIdField))
			LenderReferenceID = obj.GetStringField(FGameShiftFields::LenderReferenceIdField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::BorrowerReferenceIdField))
			BorrowerReferenceID = obj.GetStringField(FGameShiftFields::BorrowerReferenceIdField);
		if (obj.HasTypedField<EJson::Number>(FGameShiftFields::ExpirationField))
			Expiration = obj.GetNumberField(FGameShiftFields::ExpirationField);
		return true;
	}
	return false;
}


FGameShiftCreateAssetCollectionRequest::FGameShiftCreateAssetCollectionRequest()
{
	Name = TEXT("");
	Description = TEXT("");
	ImageUrl = TEXT("");
}
void FGameShiftCreateAssetCollectionRequest::writeJSON(JsonWriter& writerPtr) const
{
	auto& writer = (*writerPtr);
	writer.WriteObjectStart();

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

	writer.WriteObjectEnd();
}
bool FGameShiftCreateAssetCollectionRequest::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid()) {
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::NameField))
			Name = obj.GetStringField(FGameShiftFields::NameField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::DescriptionField))
			Description = obj.GetStringField(FGameShiftFields::DescriptionField);
		if (obj.HasTypedField<EJson::Number>(FGameShiftFields::ImageUrlField))
			ImageUrl = obj.GetStringField(FGameShiftFields::ImageUrlField);
		return true;
	}
	return false;
}


FGameShiftUpdateAssetTemplateRequest::FGameShiftUpdateAssetTemplateRequest()
{
	Name = TEXT("");
	Description = TEXT("");
	SourceImage = TEXT("");
	CollectionID = TEXT("");
	Attributes.Reset();
}
void FGameShiftUpdateAssetTemplateRequest::writeJSON(JsonWriter& writerPtr) const
{
	auto& writer = (*writerPtr);
	writer.WriteObjectStart();

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
	if (!SourceImage.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::SourceImageField);
		writer.WriteValue(SourceImage);
	}

	if (!CollectionID.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::CollectionIdField);
		writer.WriteValue(CollectionID);
	}

	if (Attributes.Num() > 0)
	{
		writer.WriteArrayStart(FGameShiftFields::AttributesField);
		for (auto It = Attributes.CreateConstIterator(); It; ++It)
		{
			const FGameShiftAssetAttribute& Attibute = *It;
			Attibute.ToJson(writerPtr);
		}
		writer.WriteArrayEnd();
	}

	writer.WriteObjectEnd();
}
bool FGameShiftUpdateAssetTemplateRequest::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid()) {
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::NameField))
			Name = obj.GetStringField(FGameShiftFields::NameField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::DescriptionField))
			Description = obj.GetStringField(FGameShiftFields::DescriptionField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::SourceImageField))
			SourceImage = obj.GetStringField(FGameShiftFields::SourceImageField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::CollectionIdField))
			CollectionID = obj.GetStringField(FGameShiftFields::CollectionIdField);

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
		return true;
	}
	return false;
}


FGameShiftDestinationUserRequest::FGameShiftDestinationUserRequest()
{
	DestinationUserReferenceID = TEXT("");
}
void FGameShiftDestinationUserRequest::writeJSON(JsonWriter& writerPtr) const
{
	auto& writer = (*writerPtr);
	writer.WriteObjectStart();

	writer.WriteIdentifierPrefix(FGameShiftFields::DestinationUserReferenceIDField);
	writer.WriteValue(DestinationUserReferenceID);

	writer.WriteObjectEnd();
}
bool FGameShiftDestinationUserRequest::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid()) {
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::DestinationUserReferenceIDField))
			DestinationUserReferenceID = obj.GetStringField(FGameShiftFields::DestinationUserReferenceIDField);
		return true;
	}
	return false;
}


FGameShiftLenderReferenceRequest::FGameShiftLenderReferenceRequest()
{
	LenderReferenceID = TEXT("");
}
void FGameShiftLenderReferenceRequest::writeJSON(JsonWriter& writerPtr) const
{
	auto& writer = (*writerPtr);
	writer.WriteObjectStart();

	writer.WriteIdentifierPrefix(FGameShiftFields::LenderReferenceIdField);
	writer.WriteValue(LenderReferenceID);

	writer.WriteObjectEnd();
}
bool FGameShiftLenderReferenceRequest::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid()) {
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::LenderReferenceIdField))
			LenderReferenceID = obj.GetStringField(FGameShiftFields::LenderReferenceIdField);
		return true;
	}
	return false;
}

FGameShiftBorrowerReferenceRequest::FGameShiftBorrowerReferenceRequest()
{
	BorrowerReferenceID = TEXT("");
}
void FGameShiftBorrowerReferenceRequest::writeJSON(JsonWriter& writerPtr) const
{
	auto& writer = (*writerPtr);
	writer.WriteObjectStart();

	writer.WriteIdentifierPrefix(FGameShiftFields::BorrowerReferenceIdField);
	writer.WriteValue(BorrowerReferenceID);

	writer.WriteObjectEnd();
}
bool FGameShiftBorrowerReferenceRequest::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid()) {
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::BorrowerReferenceIdField))
			BorrowerReferenceID = obj.GetStringField(FGameShiftFields::BorrowerReferenceIdField);
		return true;
	}
	return false;
}



FGameShiftCreatePaymentForAssetRequest::FGameShiftCreatePaymentForAssetRequest()
{
	AmountCents = 0;
	Quantity = 0;
	BuyerID = TEXT("");
}
void FGameShiftCreatePaymentForAssetRequest::writeJSON(JsonWriter& writerPtr) const
{
	auto& writer = (*writerPtr);
	writer.WriteObjectStart();

	writer.WriteIdentifierPrefix(FGameShiftFields::AmountCentsField);
	writer.WriteValue(AmountCents);

	writer.WriteIdentifierPrefix(FGameShiftFields::QuantityField);
	writer.WriteValue(Quantity);
	
	if (!BuyerID.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::BuyerIdField);
		writer.WriteValue(BuyerID);
	}

	writer.WriteObjectEnd();
}
bool FGameShiftCreatePaymentForAssetRequest::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid()) {
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::Number>(FGameShiftFields::AmountCentsField))
			AmountCents = obj.GetNumberField(FGameShiftFields::AmountCentsField);
		if (obj.HasTypedField<EJson::Number>(FGameShiftFields::QuantityField))
			Quantity = obj.GetNumberField(FGameShiftFields::QuantityField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::BuyerIdField))
			BuyerID = obj.GetStringField(FGameShiftFields::BuyerIdField);
		return true;
	}
	return false;
}


FGameShiftCreatePaymentRequest::FGameShiftCreatePaymentRequest()
{
	Title = TEXT("");
	Description = TEXT("");
	AmountCents = 0;
	Quantity = 0;
	BuyerID = TEXT("");
}
void FGameShiftCreatePaymentRequest::writeJSON(JsonWriter& writerPtr) const
{
	auto& writer = (*writerPtr);
	writer.WriteObjectStart();

	if (!Title.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::TitleField);
		writer.WriteValue(Title);
	}

	if (!Description.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::DescriptionField);
		writer.WriteValue(Description);
	}

	writer.WriteIdentifierPrefix(FGameShiftFields::AmountCentsField);
	writer.WriteValue(AmountCents);
	
	writer.WriteIdentifierPrefix(FGameShiftFields::QuantityField);
	writer.WriteValue(Quantity);

	if (!BuyerID.IsEmpty())
	{
		writer.WriteIdentifierPrefix(FGameShiftFields::BuyerIdField);
		writer.WriteValue(BuyerID);
	}

	writer.WriteObjectEnd();
}
bool FGameShiftCreatePaymentRequest::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	if (objPtr.IsValid()) {
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::TitleField))
			Title = obj.GetStringField(FGameShiftFields::TitleField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::DescriptionField))
			Description = obj.GetStringField(FGameShiftFields::DescriptionField);
		if (obj.HasTypedField<EJson::Number>(FGameShiftFields::AmountCentsField))
			AmountCents = obj.GetNumberField(FGameShiftFields::AmountCentsField);
		if (obj.HasTypedField<EJson::Number>(FGameShiftFields::QuantityField))
			Quantity = obj.GetNumberField(FGameShiftFields::QuantityField);
		if (obj.HasTypedField<EJson::String>(FGameShiftFields::BuyerIdField))
			BuyerID = obj.GetStringField(FGameShiftFields::BuyerIdField);
		return true;
	}
	return false;
}


FGameShiftUsersResult::FGameShiftUsersResult()
{
	Users.Reset();
}
void FGameShiftUsersResult::writeJSON(JsonWriter& writer) const 
{
	FGameShiftMetaBasedResult::writeJSON(writer);
}
bool FGameShiftUsersResult::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	Users.Reset();
	FGameShiftMetaBasedResult::readFromValue(objPtr);
	if (objPtr.IsValid()) {
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::Array>(FGameShiftFields::DataField))
		{
			const TArray<TSharedPtr<FJsonValue>>& DataArrayJson = obj.GetArrayField(FGameShiftFields::DataField);
			for (auto It = DataArrayJson.CreateConstIterator(); It; ++It)
			{
				const TSharedPtr<FJsonValue>& DataJsonPtr = *It;
				if (DataJsonPtr.IsValid())
				{
					FGameShiftUserAccount Account = FGameShiftUserAccount();
					Account.FromJson(DataJsonPtr->AsObject());
					Users.Add(Account);
				}
			}
		}
		return true;
	}
	return false;
}

FGameShiftAssetsResult::FGameShiftAssetsResult()
{
	Assets.Reset();
}
void FGameShiftAssetsResult::writeJSON(JsonWriter& writer) const
{

}
bool FGameShiftAssetsResult::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	Assets.Reset();
	FGameShiftMetaBasedResult::readFromValue(objPtr);
	if (objPtr.IsValid()) {
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::Array>(FGameShiftFields::DataField))
		{
			const TArray<TSharedPtr<FJsonValue>>& DataArrayJson = obj.GetArrayField(FGameShiftFields::DataField);
			for (auto It = DataArrayJson.CreateConstIterator(); It; ++It)
			{
				const TSharedPtr<FJsonValue>& DataJsonPtr = *It;
				if (DataJsonPtr.IsValid())
				{
					FGameShiftAsset Account = FGameShiftAsset();
					Account.FromJson(DataJsonPtr->AsObject());
					Assets.Add(Account);
				}
			}
		}
		return true;
	}
	return false;
}

FGameShiftAssetResult::FGameShiftAssetResult()
{
	Asset = FGameShiftAsset();
}
void FGameShiftAssetResult::writeJSON(JsonWriter& writer) const
{
	Asset.ToJson(writer);
}
bool FGameShiftAssetResult::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	return Asset.FromJson(objPtr);
}

FGameShiftStringResult::FGameShiftStringResult()
{
	Response = TEXT("");
}
void FGameShiftStringResult::writeJSON(JsonWriter& writer) const
{

}
bool FGameShiftStringResult::readFromValue(const TSharedPtr<FJsonObject>& obj)
{
	return false;
}
bool FGameShiftStringResult::readFromString(const FString& String)
{
	Response = String;
	return true;
}



FGameShiftAssetTransferResult::FGameShiftAssetTransferResult()
{
	Url = TEXT("");
}
void FGameShiftAssetTransferResult::writeJSON(JsonWriter& writer) const
{

}
bool FGameShiftAssetTransferResult::readFromValue(const TSharedPtr<FJsonObject>& obj)
{
	return false;
}
bool FGameShiftAssetTransferResult::readFromString(const FString& String)
{
	Url = String;
	return true;
}

FGameShiftLendGrantResult::FGameShiftLendGrantResult()
{
	LendGrant = FGameShiftLendGrant();
}
void FGameShiftLendGrantResult::writeJSON(JsonWriter& writer) const
{
	LendGrant.ToJson(writer);
}
bool FGameShiftLendGrantResult::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	return LendGrant.FromJson(objPtr);
}



FGameShiftLendAcceptResult::FGameShiftLendAcceptResult()
{
	Acception = FGameShiftLendAccepted();
}
void FGameShiftLendAcceptResult::writeJSON(JsonWriter& writer) const
{
	Acception.ToJson(writer);
}
bool FGameShiftLendAcceptResult::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	return Acception.FromJson(objPtr);
}



void FGameShiftNullRequest::writeJSON(JsonWriter& writer) const
{

}
bool FGameShiftNullRequest::readFromValue(const TSharedPtr<FJsonObject>& obj)
{
	return false;
}

FGameShiftAssetCollectionsResult::FGameShiftAssetCollectionsResult()
{
	Collections.Reset();
}
void FGameShiftAssetCollectionsResult::writeJSON(JsonWriter& writer) const
{
	FGameShiftMetaBasedResult::writeJSON(writer);
}
bool FGameShiftAssetCollectionsResult::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	Collections.Reset();
	FGameShiftMetaBasedResult::readFromValue(objPtr);
	if (objPtr.IsValid()) {
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::Array>(FGameShiftFields::DataField))
		{
			const TArray<TSharedPtr<FJsonValue>>& DataArrayJson = obj.GetArrayField(FGameShiftFields::DataField);
			for (auto It = DataArrayJson.CreateConstIterator(); It; ++It)
			{
				const TSharedPtr<FJsonValue>& DataJsonPtr = *It;
				if (DataJsonPtr.IsValid())
				{
					FGameShiftAssetCollection Collection = FGameShiftAssetCollection();
					Collection.FromJson(DataJsonPtr->AsObject());
					Collections.Add(Collection);
				}
			}
		}
		return true;
	}
	return false;
}

FGameShiftPaymentsResult::FGameShiftPaymentsResult()
{
	Payments.Reset();
}
void FGameShiftPaymentsResult::writeJSON(JsonWriter& writer) const
{
	FGameShiftMetaBasedResult::writeJSON(writer);
}
bool FGameShiftPaymentsResult::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	Payments.Reset();
	FGameShiftMetaBasedResult::readFromValue(objPtr);
	if (objPtr.IsValid()) {
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::Array>(FGameShiftFields::DataField))
		{
			const TArray<TSharedPtr<FJsonValue>>& DataArrayJson = obj.GetArrayField(FGameShiftFields::DataField);
			for (auto It = DataArrayJson.CreateConstIterator(); It; ++It)
			{
				const TSharedPtr<FJsonValue>& DataJsonPtr = *It;
				if (DataJsonPtr.IsValid())
				{
					FGameShiftPayment Payment = FGameShiftPayment();
					Payment.FromJson(DataJsonPtr->AsObject());
					Payments.Add(Payment);
				}
			}
		}
		return true;
	}
	return false;
}

FGameShiftAssetCollectionResult::FGameShiftAssetCollectionResult()
{
	Collection = FGameShiftAssetCollection();
}
void FGameShiftAssetCollectionResult::writeJSON(JsonWriter& writerPtr) const
{
	Collection.ToJson(writerPtr);
}
bool FGameShiftAssetCollectionResult::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	return Collection.FromJson(objPtr);
}

FGameShiftPaymentResult::FGameShiftPaymentResult()
{
	Payment = FGameShiftPayment();
}
void FGameShiftPaymentResult::writeJSON(JsonWriter& writerPtr) const
{
	Payment.ToJson(writerPtr);
}
bool FGameShiftPaymentResult::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	return Payment.FromJson(objPtr);
}

FGameShiftCreatedPaymentResult::FGameShiftCreatedPaymentResult()
{
	Payment = FGameShiftCreatedPayment();
}
void FGameShiftCreatedPaymentResult::writeJSON(JsonWriter& writerPtr) const
{
	Payment.ToJson(writerPtr);
}
bool FGameShiftCreatedPaymentResult::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	return Payment.FromJson(objPtr);
}

FGameShiftAssetTemplateResult::FGameShiftAssetTemplateResult()
{
	Template = FGameShiftAssetTemplate();
}
void FGameShiftAssetTemplateResult::writeJSON(JsonWriter& writerPtr) const
{
	Template.ToJson(writerPtr);
}
bool FGameShiftAssetTemplateResult::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	return Template.FromJson(objPtr);
}

FGameShiftAssetTemplatesResult::FGameShiftAssetTemplatesResult()
{
	Templates.Reset();
}
void FGameShiftAssetTemplatesResult::writeJSON(JsonWriter& writer) const
{
	FGameShiftMetaBasedResult::writeJSON(writer);
}
bool FGameShiftAssetTemplatesResult::readFromValue(const TSharedPtr<FJsonObject>& objPtr)
{
	Templates.Reset();
	FGameShiftMetaBasedResult::readFromValue(objPtr);
	if (objPtr.IsValid()) {
		const FJsonObject& obj = (*objPtr);
		if (obj.HasTypedField<EJson::Array>(FGameShiftFields::DataField))
		{
			const TArray<TSharedPtr<FJsonValue>>& DataArrayJson = obj.GetArrayField(FGameShiftFields::DataField);
			for (auto It = DataArrayJson.CreateConstIterator(); It; ++It)
			{
				const TSharedPtr<FJsonValue>& DataJsonPtr = *It;
				if (DataJsonPtr.IsValid())
				{
					FGameShiftAssetTemplate Template = FGameShiftAssetTemplate();
					Template.FromJson(DataJsonPtr->AsObject());
					Templates.Add(Template);
				}
			}
		}
		return true;
	}
	return false;
}