#include "Perceptron.h"

Perceptron::Perceptron(int pInputLayerSize, int pHiddenLayerSize, int pEpochsRequired, double pLearningRate){
	inputLayerSize = pInputLayerSize;
	hiddenLayerSize = pHiddenLayerSize;
	epochsRequired = pEpochsRequired;
	learningRate = pLearningRate;
	initWeights();
}

void Perceptron::initWeights(){
	for(int i=0; i<inputLayerSize; i++){
		inputHiddenWeights.push_back(vector<double>());
	}
	for(int i=0; i<inputLayerSize; i++){
		for(int j=0; j<hiddenLayerSize; j++){
			inputHiddenWeights[i].push_back(randomWeight());
		}
	}
	for(int i=0; i<hiddenLayerSize; i++){
		hiddenOutputWeights.push_back(randomWeight());
	}
	for(int i=0; i<hiddenLayerSize; i++){
		hiddenLayerNeurons.push_back(new Neuron());
	}	
}

double Perceptron::randomNumber(){
    return ((double)rand()/(double)RAND_MAX);
}

double Perceptron::randomWeight(){
	return -0.1 + 0.2 * randomNumber();
}

double Perceptron::sigmoidFunction(double pValue){
	return 1.0/(1+exp(-pValue));
}

double Perceptron::sigmoidDerivate(double pValue){
	return pValue * (1 - pValue);
}

void Perceptron::backPropagation(vector<int> *input, double output, double error){
	double outputDelta = error * sigmoidDerivate(output);
	for(int i=0; i<hiddenLayerSize; i++){
		hiddenOutputWeights[i] += hiddenLayerNeurons[i]->getNeuronValue() * learningRate * outputDelta; 
	}
	//Output delta for input layer
	vector<double> hiddenDeltas;
	for(int i=0; i<hiddenLayerSize; i++){
		double currentDelta = 
			sigmoidDerivate(hiddenLayerNeurons[i]->getNeuronValue()) * outputDelta * hiddenOutputWeights[i];
		hiddenDeltas.push_back(currentDelta);
	}
	for(int i=0; i<inputLayerSize; i++){
		for(int h=0; h<hiddenLayerSize; h++){
			inputHiddenWeights[i][h] += input->at(i) * learningRate * hiddenDeltas[h];
		}
	}
}

void Perceptron::train(vector < vector<int> > *trainingMatrix, vector<int> *results){
	int epochSize = results->size();
	int hits=0;
	int input = 0;
	int epochs = 0;
	while(epochSize > hits && epochs < epochsRequired){
		vector<int> currentInput = trainingMatrix->at(input);
		double output = execute(&currentInput);
		double expectedValue = 0.0;
		
		if(results->at(input) == 0){
			expectedValue = 0.25;
		}else{
			expectedValue = 0.75;
		}

		double error = expectedValue - output;

		// 0.25 is the range, the abs is used to check if the value is in the correct range
		if(abs(error) <= 0.01)
			hits++;
		else{
			hits = 0;
			backPropagation(&currentInput, expectedValue, error);
		}
		
		input++;
		
		if(input == epochSize){
			epochs++;
			input = 0;
		}
	}
	cout << "Resultados del entrenamiento" << endl;
	cout << "HITS: " << hits << endl;
	cout << "EPOCHS: " << epochs << endl;
}

double Perceptron::execute(vector<int> *input){
	double output = 0;
	for(int h=0; h<hiddenLayerSize; h++){
		double sums = 0;
		for(int i=0; i<inputLayerSize; i++){
			sums += input->at(i) * inputHiddenWeights[i][h];
		}
		hiddenLayerNeurons[h]->setNeuronValue(sigmoidFunction(sums));
	}

	for(int h=0; h<hiddenLayerSize; h++){
		output += hiddenLayerNeurons[h]->getNeuronValue() * hiddenOutputWeights[h];
	}
	output = sigmoidFunction(output);
	return output;	
}