#include <iostream>

class Neuron{
	public:
		Neuron();
		Neuron(double);
		double getNeuronValue();
		void setNeuronValue(double);
	private:
		double neuronValue;
};