CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic
TARGET := test_tracker
SRCS := task_tracker.cpp task_tracker_test.cpp
OBJS := $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
