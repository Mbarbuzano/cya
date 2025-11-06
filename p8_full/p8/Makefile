CXX = g++
CXXFLAGS = -Wall -std=c++23

SRC = main.cc grammar.cc
OBJ = $(SRC:.cc=.o)
EXEC = Grammar2CNF

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)