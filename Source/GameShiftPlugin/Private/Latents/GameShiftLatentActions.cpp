
#include "Latents/GameShiftLatentActions.h"
#include "Engine/Engine.h"



FGameShiftLatentAction::FGameShiftLatentAction(const FGameShiftErrorSignature& InOnError, const FLatentActionInfo& LatentInfo)
	: OnError(InOnError)
	, bCompleted(false)
	, bInitialized(false)
	, ExecutionFunction(LatentInfo.ExecutionFunction)
	, OutputLink(LatentInfo.Linkage)
	, CallbackTarget(LatentInfo.CallbackTarget)
{

}
void FGameShiftLatentAction::UpdateOperation(FLatentResponse& Response)
{
	if (!bInitialized)
	{
		if (!DoGameShiftRequest())
			bCompleted = true;
		bInitialized = true;
	}
	Response.FinishAndTriggerIf(bCompleted, ExecutionFunction, OutputLink, CallbackTarget);
}
void FGameShiftLatentAction::OnErrorEvent(const FGameShiftCppError& Error)
{
	bCompleted = true;
	OnError.ExecuteIfBound(Error);
}
GameShiftAPIPtr FGameShiftLatentAction::GetAPI() const
{
	return IGameShiftModuleInterface::Get().GetAPI();
}
FGameShiftErrorDelegate FGameShiftLatentAction::CreateErrorDelegate()
{
	return FGameShiftErrorDelegate::CreateRaw(this, &FGameShiftLogin::OnErrorEvent);
}