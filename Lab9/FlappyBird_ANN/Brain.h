#pragma once

#include <time.h>
#include <cstdlib>

// Not a very generic Brain unfortunately.
// Had to hardcode in the architecture for this one.

class Brain
{


public:
	int numInputs = 5;
	int numHidden = 4;
	int numOutputs = 1;
	float **weightsLayer1;	// From inputs to hidden layer
	float *weightsLayer2;	// From hidden layer to output neuron
	float *biases;
	int source = 0;			// Just to keep track of where the NN weightrs came from
							// 0 = GA
							// 1 = BP

	bool useBiases = true;	// If set to false no Bias values will be used.
							// If true, the Biases will be included in Crossover and Mutation.

	Brain();
	~Brain();
	void init(int inputs, int hidden, int outputs);
	
	// Evaluate inputs on the network
	int FeedForward(float *inputs);

	// Rectified Linear Unit activation Function
	float ReLu(float val);

	// Softmax or averaging the value
	void SoftMax(float *data, int len);

	// Sigmoid Activation Function
	float Sigmoid(float z);
};

