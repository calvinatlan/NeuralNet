#ifndef NET
#define NET

#include <vector>

#include "neuron.h"

using namespace std;

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

#endif
