
#pragma once

#include "UObject/NoExportTypes.h"
#include "NeuralLayer.h"
#include "SigmoidNeuralLayer.h"
#include "HyperbolicTangentNeuralLayer.h"
#include "NeuralNet.generated.h"

/**
 * 
 */

UCLASS(BlueprintType)
class AUTONOMOUSCAR_API UNeuralNet : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UNeuralLayer*> layers;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool hasBiasNeurons = false;

	UFUNCTION(BlueprintCallable)
		TArray<float> output(UPARAM(ref) TArray<float> input);
	UFUNCTION(BlueprintCallable)
		void addLayer(UPARAM(ref) UNeuralLayer* layer);
	UFUNCTION(BlueprintCallable)
		void initWeights();
	UFUNCTION(BlueprintCallable)
		void initNet(int32 numOfHiddenLayers, int32 numOfInputs, int32 hiddenLayerSize, int32 numOfOutputs, bool biasNeurons);
	UFUNCTION(BlueprintCallable)
		void initNetWithWeights(int32 numOfHiddenLayers, int32 numOfInputs, int32 hiddenLayerSize, int32 numOfOutputs, bool biasNeurons, TArray<float> weights);
	UFUNCTION(BlueprintCallable)
		void printNeuronWeights();
	UFUNCTION()
		TArray<float> normalizeInputs(TArray<float> inputs);

	UFUNCTION(BlueprintCallable)
		float error(float distance, float totalDistance, float time);

	UFUNCTION(BlueprintCallable)
		TArray<float> getFlatWeights();
	UFUNCTION(BlueprintCallable)
		int32 getNumOfHiddenLayers();
	UFUNCTION(BlueprintCallable)
		int32 getHiddenLayerSize();
	UFUNCTION(BlueprintCallable)
		int32 getNumOfInputs();
	UFUNCTION(BlueprintCallable)
		int32 getNumOfOutputs();
	UFUNCTION(BlueprintCallable)
		void setWeights(TArray<float> flatWeights);

	const float MIN_SENSOR_INPUT = 0;
	//distance of linetrace on sensors
	const float MAX_SENSOR_INPUT = 30000;
	const float MIN_SPEED_INPUT = 0;
	//216 kmh, limited by tracks more than vehicle capability
	const float MAX_SPEED_INPUT = 6000;

};
