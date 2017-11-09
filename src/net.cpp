#include <vector>
#include <iostream>
#include <cassert>
#include <cstdlib>

#include "net.h"
#include "neuron.h"

using namespace std;

void Net::feedForward(const vector<double> &inputVals)
{
    assert(inputVals.size() == m_layers[0].size() - 1);

    // Assign (latch) the input values into the input neurons
    for(unsigned i = 0; i < inputVals.size(); ++i){
        m_layers[0][i].setOutputVal(inputVals[i]);
    }

    //Forward propagation
    for(unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum){
        Layer &prevLayer = m_layers[layerNum - 1];
        for(unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n){
            m_layers[layerNum][n].feedForward(prevLayer);
        }
    }
}

Net::Net(const vector<unsigned> &topology)
{
    unsigned numLayers = topology.size();
    for(unsigned layerNum = 0; layerNum < numLayers; ++layerNum){
        m_layers.push_back(Layer());

        //If it's the last layer, it has no outputs
        //if not, it has as many outputs as there are neurons on the next layer
        //(except bias neurons)
        unsigned numOutputs = layerNum == topology.size() - 1 ? 0 :
            topology[layerNum + 1];

        //Add neurons per layer, use <= to have an extra neuron for bias
        for(unsigned neuronNum = 0; neuronNum <= topology[layerNum];
            ++neuronNum)
        {
            m_layers.back().push_back(Neuron(numOutputs, neuronNum));
            cout << "Made a neuron" << endl;
        }
    }
}
