SRC_DIR := src
BIN_DIR := bin

EXEC_NAME := mood

SRCS := $(shell find $(SRC_DIR) -type f -name '*.c')
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRCS))

CC := gcc
CFLAGS := -Wall -Wextra

LDFLAGS := -lSDL2 -lSDL2_image

LOGGER = @echo "[$(notdir $<)]"

all: $(BIN_DIR)/$(EXEC_NAME)

debug: CFLAGS += -DDEBUG_LOGGING
debug: $(BIN_DIR)/$(EXEC_NAME)

$(BIN_DIR)/$(EXEC_NAME): $(OBJS)
	$(LOGGER) Linking...
	@mkdir -p $(BIN_DIR)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "done."

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(LOGGER) Compiling...
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(F) -c -o $@ $<
	@echo "done."

start:
	@echo "$(EXEC_NAME) Build"

clean:
	rm -rf $(BIN_DIR)

.PHONY: all debug start clean install

install:
	@sudo ln -fs $(shell realpath $(BIN_DIR)/$(EXEC_NAME)) /usr/local/bin/$(EXEC_NAME)
	@echo "Installed $(EXEC_NAME) to PATH"
