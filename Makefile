# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude

# Directories
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build
BIN_DIR = bin

# Targets
MAIN_TARGET = render
TEST_TARGET = test_suite
MAIN_SRC = $(SRC_DIR)/main.cpp
MAIN_OBJ = $(BUILD_DIR)/main.o
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_SRCS))

all: $(BIN_DIR)/$(MAIN_TARGET) $(BIN_DIR)/$(TEST_TARGET)

$(BIN_DIR)/$(MAIN_TARGET): $(MAIN_OBJ)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BIN_DIR)/$(TEST_TARGET): $(TEST_OBJS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

test: $(BIN_DIR)/$(TEST_TARGET)
	./$(BIN_DIR)/$(TEST_TARGET)

run: $(BIN_DIR)/$(MAIN_TARGET)
	./$(BIN_DIR)/$(MAIN_TARGET)

.PHONY: all clean test run