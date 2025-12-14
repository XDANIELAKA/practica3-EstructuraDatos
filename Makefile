CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude
BUILD_DIR = build
SRC_DIR = src
BIN = programa

SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/contacto.cpp $(SRC_DIR)/agendacontactos.cpp
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(BIN)

doc:
	doxygen doc/Doxyfile

.PHONY: all clean doc