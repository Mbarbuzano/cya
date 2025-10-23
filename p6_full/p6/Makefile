CXX = g++
CXXFLAGS = -Wall -std=c++23

SRC = automaton.cc main.cc
OBJ = $(SRC:.cc=.o)
EXEC = p06_automata_simulator

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)