
#include "AutonomousCar.h"
#include "NeuralLayer.h"


TArray<float> UNeuralLayer::output(TArray<float> inputs) {
	TArray<float> outputs;
	for (UNeuron* neuron : neurons) {
		float neuronOutput = neuron->output(inputs);
		outputs.Add(neuronOutput);
	}
	return outputs;
}


void UNeuralLayer::constructLayer(int32 numOfNeurons, int32 inputsSize) {
	inputSize = inputsSize;
	for (int32 i = 0; i < numOfNeurons; i++) {
		UNeuron* newNeuron = NewObject<UNeuron>(this);
		TArray<float> weights;
		weights.Init(0, inputsSize);
		newNeuron->weights = weights;
		bindFuncToNeuron(newNeuron);
		neurons.Add(newNeuron);
	}
}

void UNeuralLayer::constructLayerWithBiasNeuron(int32 numOfNeurons, int32 inputsSize){
	constructLayer(numOfNeurons-1, inputsSize);
	UNeuron* biasNeuron = NewObject<UBiasNeuron>(this);
	TArray<float> weights;
	weights.Init(0, inputsSize);
	biasNeuron->weights = weights;

	neurons.Add(biasNeuron);
	inputSize = inputsSize;
}

void UNeuralLayer::initWeights() {
	for (UNeuron* neuron : neurons) {
		neuron->initWeights();
	}
}

void UNeuralLayer::setWeights(TArray<float> newWeights) {
	int index = 0;
	for (UNeuron* neuron : neurons) {
		TArray<float> neuronWeights;
		neuronWeights.Append(&newWeights[index], inputSize);
		neuron->setWeights(neuronWeights);
		index += inputSize;
	}
}

int32 UNeuralLayer::getLayerSize() {
	return neurons.Num();
}

int32 UNeuralLayer::getInputSize() {
	return inputSize;
}

void UNeuralLayer::bindFuncToNeuron(UNeuron* neuron) {
	neuron->transferFuncDel.BindLambda([](float x) {
		return x;
	});
}


