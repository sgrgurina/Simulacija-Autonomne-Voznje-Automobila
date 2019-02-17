
#pragma once

#include "NeuralLayer.h"
#include "HyperbolicTangentNeuralLayer.generated.h"

/**
 * 
 */
UCLASS()
class AUTONOMOUSCAR_API UHyperbolicTangentNeuralLayer : public UNeuralLayer
{
	GENERATED_BODY()
	
public:
		UFUNCTION(BlueprintCallable)
		float tanh(UPARAM(ref) float x);

	void bindFuncToNeuron(UNeuron* neuron) override;
	
};
