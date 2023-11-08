//////////////////////////////////////////////////////
// Copyright (C) Microsoft. 2018. All rights reserved.
//////////////////////////////////////////////////////


#include "GameShift.h"

/*
eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJrZXkiOiJiMjlmYjhmOS03ODhkLTRkZDQtYWFlYy0xMzRiNjdjMWM5YjUiLCJzdWIiOiI4N2UwZjA0Mi02YzkzLTQxMGYtYjI1MS05YjMzYjY0NmY1MTMiLCJpYXQiOjE2OTkxNzU4MzN9.0CHT4pzPM2ZOkgW_xHHwJtR7HO6MvOsal9c_Na0mpe0
*/
using namespace GameShift;

FString __INVALID_HTTPVERB_STRING = TEXT("");
TMap<EVerbMode, FString> HttpVerbToStrings = {
	{EVerbMode::GET,TEXT("GET")},
	{EVerbMode::POST,TEXT("POST")},
	{EVerbMode::PUT,TEXT("PUT")},
	{EVerbMode::DELETE,TEXT("DELETE")}
};

const FString& GameShift::GetVerbString(EVerbMode Mode)
{
	FString* VerbStrPtr = HttpVerbToStrings.Find(Mode);
	return (VerbStrPtr != nullptr) ? (*VerbStrPtr) : __INVALID_HTTPVERB_STRING;
}