CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -g -O0 -I. -I/usr/include/freetype2 -MMD -MP

LIBS := -lGLEW -lGL -lglfw -lGLU -ldl -lfreetype

TARGET := main
BUILD_DIR := build

SRCS := $(wildcard src/*.cpp)

all: $(TARGET)	

src: $(TARGET)

OBJS := $(patsubst src/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
DEP := $(OBJS:.o=.d)

# build the target file with all obj file dependancies

$(TARGET) : $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o $@

# all .o files in build_dir are rebuilt if a file
# with the target name is changed
# If a file in build_dir changed, don't rebuild
$(BUILD_DIR)/%.o : src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# NOTE: $< = first-prerequisite, $@ = target

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

-include $(DEP)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild
