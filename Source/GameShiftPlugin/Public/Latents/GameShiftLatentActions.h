#pragma once

#include "CoreMinimal.h"
#include "UObject/WeakObjectPtr.h"
#include "Engine/LatentActionManager.h"
#include "Engine/Public/LatentActions.h"
#include "GameShiftBaseModel.h"
#include "GameShiftPlugin.h"

class FGameShiftLatentAction : public FPendingLatentAction
{
public:

	FGameShiftLatentAction(const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo);

protected:

	GameShiftAPIPtr GetAPI() const;

	virtual bool DoGameShiftRequest() { return false; }
	FGameShiftErrorSignature OnError;

	bool bCompleted;
	bool bInitialized;
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;

	virtual void UpdateOperation(FLatentResponse& Response) override;

	FGameShiftErrorDelegate CreateErrorDelegate();
	void OnErrorEvent(const FGameShiftCppError& Error);
};