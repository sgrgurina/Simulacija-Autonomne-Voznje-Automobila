
#pragma once

#include "UObject/NoExportTypes.h"
#include "Neuron.generated.h"

DECLARE_DELEGATE_RetVal_OneParam(float, TransferFunctionDelegate, float);
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class AUTONOMOUSCAR_API UNeuron : public UObject
{
	GENERATED_BODY()

public:
	TransferFunctionDelegate transferFuncDel;

	UPROPERTY(BlueprintReadWrite)
		TArray<float> weights;

	UFUNCTION(BlueprintCallable)
		virtual float sumOutput(UPARAM(ref) TArray<float> inputs);
	UFUNCTION(BlueprintCallable)
		virtual float output(UPARAM(ref) TArray<float> inputs);
	UFUNCTION(BlueprintCallable)
		virtual void setWeights(UPARAM(ref) TArray<float> newWeights);
	UFUNCTION()
		virtual void initWeights();


};
