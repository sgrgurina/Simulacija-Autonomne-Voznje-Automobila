
#include "AutonomousCar.h"
#include "GenericPlatformMath.h"
#include "SigmoidNeuralLayer.h"

float USigmoidNeuralLayer::sigmoid(float x) {
	return 1.0 / (1.0 + FGenericPlatformMath::Exp(-x));
}

void USigmoidNeuralLayer::bindFuncToNeuron(UNeuron* neuron) {
	neuron->transferFuncDel.BindUFunction(this, FName("sigmoid"));
}

