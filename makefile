CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra

LIBS := -lGLEW -lGL -lglfw -lGLU

TARGET := main
BUILD_DIR := build

SRCS := $(wildcard *.cpp)


# get the pattern .cpp and replace it with .o and move it to build
OBJS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRCS))
DEP := $(OBJS:.o=.d)

all: $(TARGET)	

$(TARGET) : $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o $@

$(BUILD_DIR)/%.o : %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

-include $(DEP)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild
