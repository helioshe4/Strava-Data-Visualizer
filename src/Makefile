CXX = g++
CXXFLAGS = -std=c++17 -Wall -I ../include
LIBS = -lcurl

SRCS = api.cpp 
OBJS = $(SRCS:.cpp=.o)
EXECUTABLE = program

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LIBS)

api.o: api.cpp ../include/api.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXECUTABLE)

