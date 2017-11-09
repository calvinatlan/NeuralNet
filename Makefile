CXX = g++
CXXFLAGS = -Wall -g
ODIR = objects
SDIR = src
BDIR = build

_OBJS = main.o neuron.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.o: $(SDIR)/%.cpp
	mkdir -p objects
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(BDIR)/neural-net: $(OBJS)
	mkdir -p build
	$(CXX) -o $@ $^ $(CXXFLAGS)
