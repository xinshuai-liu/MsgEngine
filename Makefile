SRC_DIR = ./src
BUILD_DIR = ./build
TARGET = ./app

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

COMPILER = gcc
CFLAGS = -Wall

all: $(TARGET)

$(TARGET): $(OBJ) | $(BUILD_DIR)
	$(COMPILER) $^ -o $@

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(COMPILER) -c $(CFLAGS) $< -o $@

.PHONY: all clean test
clean:
	rm -rf $(BUILD_DIR)/* $(TARGET)

test:
	echo "test..."
