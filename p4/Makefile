CXX = g++
CXXFLAGS = -Wall -std=c++23

SRC = 
OBJ = $(SRC:.cc=.o)
EXEC = p04_code_analyzer

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)