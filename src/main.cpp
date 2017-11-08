#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace std;

struct Connection
{
    double weight;
    double deltaWeight;
};

//Front reference for typedef
class Neuron;

typedef vector<Neuron> Layer;

// ********** class Neuron *********

class Neuron
{
public:
    Neuron(unsigned numOutputs, unsigned myIndex);
    void setOutputVal(double val){ m_outputVal = val; }
    double getOutputVal(void) const{ return m_outputVal; }
    void feedForward(const Layer &prevLayer);

private:
    static double randomWeight(void) { return rand() / double(RAND_MAX); }
    unsigned m_myIndex;
    double m_outputVal;
    vector<Connection> m_outputWeights;
};

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

// ********** class Net *********

class Net
{
public:
    Net(const vector<unsigned> &topology);
    void feedForward(const vector<double> &inputVals);
    void backProp(const vector<double> &targetVals){};
    void getResults(const vector<double> &resultsVals) const {};

private:
    vector<Layer> m_layers;
};

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

int main()
{
    vector<unsigned> topology;
    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(1);
    Net myNet(topology);

    vector<double> inputVals;
    myNet.feedForward(inputVals);

    vector<double> targetVals;
    myNet.backProp(targetVals);

    vector<double> resultVals;
    myNet.getResults(resultVals);
}
