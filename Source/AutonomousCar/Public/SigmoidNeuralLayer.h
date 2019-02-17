
#pragma once

#include "NeuralLayer.h"
#include "SigmoidNeuralLayer.generated.h"

/**
 * 
 */
UCLASS()
class AUTONOMOUSCAR_API USigmoidNeuralLayer : public UNeuralLayer
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		float sigmoid(UPARAM(ref) float x);
	
	void bindFuncToNeuron(UNeuron* neuron) override;
	
};
