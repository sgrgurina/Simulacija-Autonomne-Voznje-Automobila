
#include "AutonomousCar.h"
#include "GenericPlatformMath.h"
#include "HyperbolicTangentNeuralLayer.h"

float UHyperbolicTangentNeuralLayer::tanh(float x) {
	return (1 - FGenericPlatformMath::Exp(-2 * x)) / (1 + FGenericPlatformMath::Exp(-2 * x));
}

void UHyperbolicTangentNeuralLayer::bindFuncToNeuron(UNeuron* neuron) {
	neuron->transferFuncDel.BindUFunction(this, FName("tanh"));
}


