
#pragma once

#include "CoreMinimal.h"
#include "GameShiftAPISettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class GAMESHIFTPLUGIN_API UGameShiftRuntimeSettings : public UObject
{
	GENERATED_BODY()
public:
	UGameShiftRuntimeSettings();

	// URL endpoint of the PlayFab production environment
	UPROPERTY(EditAnywhere, config, Category = Settings)
	FString ProductionEnvironmentURL;

	// Secret Key, Do not add this to the clients!
	UPROPERTY(EditAnywhere, config, Category = Settings)
	FString DeveloperSecretKey;
};


/**
* The settings that can be used (optionally) by instance versions of PlayFab APIs.
*/
class GAMESHIFTPLUGIN_API FGameShiftAPISettings
{

public:

	FGameShiftAPISettings(){}
    FString GeneratePfUrl(const FString& urlPath)
    {
        const UGameShiftRuntimeSettings* rSettings = GetDefault<UGameShiftRuntimeSettings>();
        if (rSettings->ProductionEnvironmentURL.StartsWith(TEXT("https://")))
        	return rSettings->ProductionEnvironmentURL + urlPath;
        else
        	return TEXT("https://") + rSettings->ProductionEnvironmentURL + urlPath;
    }
};
