// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameShiftPlugin.h"
#include "GameShiftAPI.h"
#include "Templates/SharedPointer.h"
#include "GameShiftAPISettings.h"

#if WITH_EDITOR
	#include "ISettingsModule.h"
	#include "ISettingsSection.h"
#endif // WITH_EDITOR

#define LOCTEXT_NAMESPACE "FGameShiftPluginModule"
DEFINE_LOG_CATEGORY(LogGameShift);

class FGameShiftPluginModule : public IGameShiftModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual GameShiftAPIPtr GetAPI() const override { return GameAPI; }

protected:

	void RegisterSettings();
	void UnregisterSettings();

	GameShiftAPIPtr GameAPI;
};



void FGameShiftPluginModule::StartupModule()
{
	//PlayFab::PlayFabSettings::sdkVersion = IPlayFabCommonModuleInterface::Get().GetSdkVersion();
	GameAPI = MakeShareable<UGameShiftAPI>(new UGameShiftAPI());
	RegisterSettings();
}

void FGameShiftPluginModule::ShutdownModule()
{
	UnregisterSettings();
}
void FGameShiftPluginModule::RegisterSettings()
{
#if WITH_EDITOR
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "GameShift",
			LOCTEXT("GameShiftSettingsName", "GameShift"),
			LOCTEXT("GameShiftSettingsDescription", "Configure the GameShift plugin"),
			GetMutableDefault<UGameShiftRuntimeSettings>()
		);
	}
#endif // WITH_EDITOR
}
void FGameShiftPluginModule::UnregisterSettings()
{
#if WITH_EDITOR
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "GameShift");
	}
#endif
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGameShiftPluginModule, GameShiftPlugin)