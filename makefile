CXX := g++ # Or clang++ if you prefer
CXXFLAGS := -std=c++11 -Wall -I/opt/homebrew/Cellar/sfml/2.6.1/include
LDFLAGS := -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system

SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:.cpp=.o)
EXEC := MyProject

all: $(EXEC)
# Note: The next line starts with a tab, not spaces
$(EXEC): $(OBJ)
# Note: The next line starts with a tab
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
# Note: The next line starts with a tab
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
# Note: The next line starts with a tab
	rm -f $(OBJ) $(EXEC)
