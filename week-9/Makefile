CXX := g++
CXXFLAGS := -Wall -g

FILES := main.cpp distributions.cpp generateHistogram.cpp generateBackground.cpp subtractBackground.cpp
EXECUTABLE := main
INCLUDES := -Iinclude -Iuser
SOURCE := src

OBJECTS := $(FILES:.cpp=.o)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJECTS) -o $(EXECUTABLE)
	
%.o: $(SOURCE)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
	
main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c main.cpp -o main.o

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)