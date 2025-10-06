CXX = g++
CXXFLAGS = -Wall -std=c++23

SRC = main.cc comment.cc loop.cc variable.cc analyser.cc
OBJ = $(SRC:.cc=.o)
EXEC = p04_code_analyser

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)