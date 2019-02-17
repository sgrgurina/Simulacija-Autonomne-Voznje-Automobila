
#pragma once

#include "UObject/NoExportTypes.h"
#include "Neuron.h"
#include "BiasNeuron.h"
#include "NeuralLayer.generated.h"


/**
 * 
 */
UCLASS(BlueprintType)
class AUTONOMOUSCAR_API UNeuralLayer : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UNeuron*> neurons;
	UPROPERTY()
		int32 inputSize;

	UFUNCTION(BlueprintCallable)
		TArray<float> output(UPARAM(ref) TArray<float> inputs);

	UFUNCTION(BlueprintCallable)
		virtual void constructLayer(UPARAM(ref) int32 numOfNeurons, int32 inputsSize);
	UFUNCTION(BlueprintCallable)
		void constructLayerWithBiasNeuron(UPARAM(ref) int32 numOfNeurons, int32 inputsSize);
	UFUNCTION(BlueprintCallable)
		void initWeights();
	UFUNCTION(BlueprintCallable)
		void setWeights(TArray<float> newWeights);
	UFUNCTION(BlueprintCallable)
		int32 getLayerSize();
	UFUNCTION(BlueprintCallable)
		int32 getInputSize();
	

	virtual void bindFuncToNeuron(UNeuron* neuron);
};
