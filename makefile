CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -g -O2 -I. -I/usr/include/freetype2 -MMD -MP

LIBS := -lGLEW -lGL -lglfw -lGLU -lfreetype

TARGET := main
BUILD_DIR := build

SELECT_SRC := main.cpp window.cpp
SRCS := $(wildcard *.cpp)

# get the pattern .cpp and replace it with .o and move it to build

SELECT_SRC := $(SRCS)

all: $(TARGET)	

src: $(TARGET)

OBJS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SELECT_SRC))
DEP := $(OBJS:.o=.d)

# build the target file with all obj file dependancies

$(TARGET) : $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o $@

# all .o files in build_dir are rebuilt if a file
# with the target name is changed
# If a file in build_dir changed, don't rebuild
$(BUILD_DIR)/%.o : %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# NOTE: $< = first-prerequisite, $@ = target

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

-include $(DEP)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild
