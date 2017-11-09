#include "neuron.h"

void Neuron::feedForward(const Layer &prevLayer)
{
    double sum = 0.0;

    for(unsigned n = 0; n < prevLayer.size(); ++n){
        sum += prevLayer[n].getOutputVal() *
            prevLayer[n].m_outputWeights[m_myIndex].weight;
    }

    //m_outputVal = transferFunction(sum);
}

Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
{
    for(unsigned c = 0; c < numOutputs; ++c){
        m_outputWeights.push_back(Connection());
        m_outputWeights.back().weight = randomWeight();
    }

    m_myIndex = myIndex;
}
