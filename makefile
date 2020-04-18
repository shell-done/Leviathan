EXEC=Leviathan

SRC_DIR = ./src
BUILD_DIR = ./build

SRC = $(shell find $(SRC_DIR) -name '*.cpp')
OBJ = $(SRC:%=$(BUILD_DIR)/%.o)
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS = -Wall -Wextra -g
CXX = g++

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(EXEC)

rebuild:
	@make clean
	@make

MKDIR_P ?= @mkdir -p