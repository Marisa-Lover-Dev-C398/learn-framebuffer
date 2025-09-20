CC = gcc
CFLAGS = -Wall -O2
BIN_DIR = bin
LDFLAGS = -lm

all: $(BIN_DIR)/learn-fb $(BIN_DIR)/sine 

$(BIN_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/learn-fb $(BIN_DIR)/sine
