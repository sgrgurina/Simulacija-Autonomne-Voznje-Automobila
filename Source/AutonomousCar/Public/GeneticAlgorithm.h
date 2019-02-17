
#pragma once

#include "UObject/NoExportTypes.h"
#include "NeuralNet.h"
#include "GeneticAlgorithm.generated.h"

USTRUCT()
struct FWeightsArray
{
	GENERATED_USTRUCT_BODY()
public:
		UPROPERTY()
		TArray<float> weights;

};

typedef TPair<FWeightsArray, float> FNetErrorPair;

/**
 * 
 */
UCLASS(BlueprintType)
class AUTONOMOUSCAR_API UGeneticAlgorithm : public UObject
{
	GENERATED_BODY()

public:

	TArray<FNetErrorPair> netErrorPairs;

	UPROPERTY()
		float mutationScale =0.2;
	UPROPERTY()
		float mutationProb = 0.5;
	UPROPERTY()
		int32 populationSize = 20;
	UPROPERTY()
		int32 elitism = 4;

	UFUNCTION(BlueprintCallable)
		void setProperties(float mutScale, float mutProb, int32 popSize, int32 elitismValue);
	UFUNCTION()
		TArray<float> crossover(TArray<float> parent1, TArray<float> parent2);
	UFUNCTION()
		void mutate(TArray<float> weights);
	UFUNCTION()
		TArray<FWeightsArray> getParents();
	UFUNCTION(BlueprintCallable)
		void step(TArray<UNeuralNet*> nets, TArray<float> errorValues);

};
