
#include "AutonomousCar.h"
#include <random>
#include "Neuron.h"

float UNeuron::sumOutput(TArray<float> inputs)
{
	float sum = 0;
	if(inputs.Num()>0){
		for (int32 i = 0; i < inputs.Num(); i++) {
			sum += inputs[i] * this->weights[i];
		}
	}
	return sum;
}

float UNeuron::output(TArray<float> inputs) {
	return transferFuncDel.Execute(sumOutput(inputs));
}

void UNeuron::setWeights(TArray<float> newWeights) {
	this->weights.Empty();
	for (float weight : newWeights){
		this->weights.Add(weight);
	}
}

void UNeuron::initWeights() {
	for (int i = 0; i < weights.Num(); i++) {
		std::random_device rd;

		std::mt19937 gen(rd());

		std::normal_distribution<> d(0,0.5);
		weights[i] = d(gen);
	}
}


