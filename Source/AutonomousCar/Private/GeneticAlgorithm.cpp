
#include "AutonomousCar.h"
#include <random>
#include "GeneticAlgorithm.h"



void UGeneticAlgorithm::setProperties(float mutScale, float mutProb, int32 popSize, int32 elitismValue) {
	this->mutationScale = mutScale;
	this->mutationProb = mutProb;
	this->populationSize = popSize;
	this->elitism = elitismValue;
}

TArray<float> UGeneticAlgorithm::crossover(TArray<float> parent1, TArray<float> parent2) {
	TArray<float> newWeights;

	std::random_device rd;

	std::mt19937 gen(rd());

	std::uniform_real_distribution<> uniformDist(0, 1);

	for (int32 i = 0; i < parent1.Num(); i++) {
		float p = uniformDist(gen);
		if (p < 0.5) {
			newWeights.Add(parent1[i]);
		}
		else {
			newWeights.Add(parent2[i]);
		}
	}

	return newWeights;
}

void UGeneticAlgorithm::mutate(TArray<float> weights) {
	for (int32 i = 0; i < weights.Num(); i++) {
		std::random_device rd;

		std::mt19937 gen(rd());

		std::uniform_real_distribution<> uniformDist(0, 1);

		if (uniformDist(gen) <= mutationProb) {
			std::normal_distribution<> d(0, mutationScale);

			weights[i] += d(gen);
		}

	}
}

TArray<FWeightsArray> UGeneticAlgorithm::getParents() {
	TArray<FWeightsArray> parents;
	int32 pickedIndex;
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> uniformDist(0, populationSize-1);

	while (parents.Num() < 2) {

		int index = uniformDist(gen);
		if (parents.Num() == 1) {
			if (pickedIndex == index) {
				continue;
			}
		}

		FWeightsArray newParent = netErrorPairs[index].Key;
		parents.Emplace(newParent);
		pickedIndex = index;

	}

	return parents;

}

 void UGeneticAlgorithm::step(TArray<UNeuralNet*> nets, TArray<float> errorValues) {
	TArray<FWeightsArray> newWeights;
	
	//pair up neural nets and error values
	netErrorPairs.Empty();
	for (int32 i = 0; i < nets.Num(); i++) {
		FNetErrorPair newPair;
		newPair.Key.weights = nets[i]->getFlatWeights();
		newPair.Value = errorValues[i];
		netErrorPairs.Emplace(newPair);
	}

	//sort by error values
	netErrorPairs.Sort([](FNetErrorPair A, FNetErrorPair B) {
		return A.Value < B.Value;
	});

	//keep the best nets
	for (int32 i = 0; i < elitism; i++) {
		FWeightsArray weightsToKeep;
		weightsToKeep.weights.Append(netErrorPairs[i].Key.weights);
		newWeights.Emplace(weightsToKeep);
	}

	//create new units to fill population
	while(newWeights.Num()<populationSize) {
		TArray<FWeightsArray> parents = getParents();
		FWeightsArray parent1 = parents[0];
		FWeightsArray parent2 = parents[1];

		FWeightsArray newUnitsWeights;
		newUnitsWeights.weights = crossover(parent1.weights, parent2.weights);
		mutate(newUnitsWeights.weights);
		newWeights.Emplace(newUnitsWeights);
	}

	for (int32 i = 0; i < nets.Num(); i++) {
		nets[i]->setWeights(newWeights[i].weights);
	}
}
