CXX = g++
CXXFLAGS = -Wall -std=c++23

SRC = p02_strings_main.cc symbol.cc chain.cc alphabet.cc
OBJ = $(SRC:.cc=.o)
EXEC = p02_strings

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)