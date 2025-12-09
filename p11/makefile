CXX = g++
CXXFLAGS = -Wall -std=c++23

SRC = subtree.cc point_types.cc subtree_main.cc
OBJ = $(SRC:.cc=.o)
EXEC = p11_emst

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)