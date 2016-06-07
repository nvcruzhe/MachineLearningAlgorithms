#include "Neuron.h"

Neuron::Neuron():neuronValue(0.0){}

Neuron::Neuron(double pNeuronValue):neuronValue(pNeuronValue){}

double Neuron::getNeuronValue(){
	return neuronValue;
}

void Neuron::setNeuronValue(double pNeuronValue){
	neuronValue = pNeuronValue;
}