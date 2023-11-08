// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class UGameShiftAPI;
typedef TSharedPtr<UGameShiftAPI> GameShiftAPIPtr;

class IGameShiftModuleInterface : public IModuleInterface
{
public:

	static inline IGameShiftModuleInterface& Get()
	{
		if (IsAvailable())
		{
			return FModuleManager::GetModuleChecked<IGameShiftModuleInterface>("GameShiftPlugin");
		}
		return FModuleManager::LoadModuleChecked<IGameShiftModuleInterface>("GameShiftPlugin");
	}
	/**
	* Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	* @return True if the module is loaded and ready to use
	*/
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("GameShiftPlugin");
	}

	virtual GameShiftAPIPtr GetAPI() const = 0;
};