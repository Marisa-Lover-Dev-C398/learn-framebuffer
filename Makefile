CC = gcc
CFLAGS = -Wall -O2
BIN_DIR = bin
LDFLAGS = -lm

all: $(BIN_DIR)/learn-fb $(BIN_DIR)/sine $(BIN_DIR)/sine2

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/%.o: %.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/learn-fb $(BIN_DIR)/sine
