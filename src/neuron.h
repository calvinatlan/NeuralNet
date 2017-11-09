#ifndef NEURON
#define NEURON

#include <vector>
using namespace std;

class Neuron;

typedef vector<Neuron> Layer;

struct Connection
{
    double weight;
    double deltaWeight;
};

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

#endif
