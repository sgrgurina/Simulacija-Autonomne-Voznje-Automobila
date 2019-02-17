
#pragma once

#include "Neuron.h"
#include "BiasNeuron.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class AUTONOMOUSCAR_API UBiasNeuron : public UNeuron
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		float output(UPARAM(ref) TArray<float> inputs) override;
	UFUNCTION(BlueprintCallable)
		void setWeights(UPARAM(ref) TArray<float> newWeights) override;
	
};
