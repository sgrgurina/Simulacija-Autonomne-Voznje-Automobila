
#include "AutonomousCar.h"
#include "NeuralNet.h"

TArray<float> UNeuralNet::output(TArray<float> inputs) {
	inputs = normalizeInputs(inputs);
	TArray<float> output = inputs;
	for (UNeuralLayer* layer : layers) {
		output = layer->output(output);
	}

	return output;
}

void UNeuralNet::addLayer(UNeuralLayer* layer) {
	layers.Add(layer);
}

void UNeuralNet::initWeights() {
	for (UNeuralLayer* layer : layers) {
		layer->initWeights();
	}
}

void UNeuralNet::initNet(int32 numOfHiddenLayers,int32 numOfInputs, int32 hiddenLayerSize, int32 numOfOutputs, bool biasNeurons) {
	hasBiasNeurons = biasNeurons;

	for (int32 i = 0; i < numOfHiddenLayers; i++) {
		UNeuralLayer* newLayer = NewObject<USigmoidNeuralLayer>(this);
		int32 inputSize = hiddenLayerSize;

		//if its the first hidden layer the previous layer size is equal to number of inputs to net
		if (i == 0) {
			inputSize = numOfInputs;
		}

		//layer with or without a bias neuron
		if (biasNeurons) {
			newLayer->constructLayerWithBiasNeuron(hiddenLayerSize, inputSize);
		}
		else {
			newLayer->constructLayer(hiddenLayerSize, inputSize);
		}

		this->addLayer(newLayer);
	}

	UNeuralLayer* outputLayer = NewObject<UHyperbolicTangentNeuralLayer>(this);
	outputLayer->constructLayer(numOfOutputs, hiddenLayerSize);
	this->addLayer(outputLayer);

	this->initWeights();

}

void UNeuralNet::initNetWithWeights(int32 numOfHiddenLayers, int32 numOfInputs, int32 hiddenLayerSize, int32 numOfOutputs, bool biasNeurons, TArray<float> weights) {

	initNet(numOfHiddenLayers, numOfInputs, hiddenLayerSize, numOfOutputs, biasNeurons);
	setWeights(weights);

}

void UNeuralNet::printNeuronWeights() {

	for (UNeuralLayer* layer : layers) {
		UE_LOG(LogTemp, Log, TEXT("Layer"));

		for (UNeuron* neuron : layer->neurons) {
			UE_LOG(LogTemp, Log, TEXT("Neuron"));
			for (float weight : neuron->weights) {
				UE_LOG(LogTemp, Log, TEXT("%f"), weight);
			}
		}
	}
}

TArray<float> UNeuralNet::normalizeInputs(TArray<float> inputs) {
	TArray<float> normalizedInputs;

	//all inputs except last (sensors)
	for (int i = 0; i < inputs.Num() -1; i++) {
		float normalizedInput = (inputs[i]- MIN_SENSOR_INPUT) / (MAX_SENSOR_INPUT-MIN_SENSOR_INPUT);
		normalizedInputs.Add(normalizedInput);
	}

	float normalizedSpeed = (inputs[inputs.Num() - 1] - MIN_SPEED_INPUT) / (MAX_SPEED_INPUT - MIN_SPEED_INPUT);
	normalizedInputs.Add(normalizedSpeed);

	return normalizedInputs;
}


float UNeuralNet::error(float distance, float totalDistance, float time) {
	if (distance == 0) {
		//larger then maximum practically attainiable error value
		return 1000;
	}
	//unreached percent of the track
	float error = (totalDistance - distance)/totalDistance*100;
	float distanceInMeters = distance / 100;
	error += time / distanceInMeters*50;
	return error;
}


TArray<float> UNeuralNet::getFlatWeights() {
	TArray<float> flatWeights;

	for (UNeuralLayer* layer : layers) {
		for (UNeuron* neuron : layer->neurons) {
			flatWeights.Append(neuron->weights);
		}
	}
	return flatWeights;
}

int32 UNeuralNet::getNumOfHiddenLayers() {
	return layers.Num() - 1;
}

int32 UNeuralNet::getHiddenLayerSize() {
	return layers[0]->neurons.Num();
}

int UNeuralNet::getNumOfInputs() {
	return layers[0]->neurons[0]->weights.Num();
}

int UNeuralNet::getNumOfOutputs() {
	return layers.Last()->neurons.Num();
}

void UNeuralNet::setWeights(TArray<float> flatWeights) {
	if (flatWeights.Num() != getFlatWeights().Num()) {
		UE_LOG(LogTemp, Log, TEXT("Size of new weights not equal to size of nets current weights"));
		UE_LOG(LogTemp, Log, TEXT("Size of new weights:%d"), flatWeights.Num());
		UE_LOG(LogTemp, Log, TEXT("Size of current weights:%d"), getFlatWeights().Num());
		return;
	}

	int32 index = 0;
	for (UNeuralLayer* layer : layers) {
		int32 totalWeightsNumForLayer = (layer->getInputSize()) * (layer->getLayerSize());
		TArray<float> layersNewWeights;
		layersNewWeights.Append(&flatWeights[index], totalWeightsNumForLayer);
		layer->setWeights(layersNewWeights);
		index += totalWeightsNumForLayer;
	}
}