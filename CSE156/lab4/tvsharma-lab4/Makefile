CC=gcc
CFLAGS=-Wall
BIN_DIR=bin
SRC_DIR=src

all: directories myclient myserver links

directories:
	@mkdir -p $(BIN_DIR)

myclient:
	$(CC) $(CFLAGS) -o $(BIN_DIR)/myclient $(SRC_DIR)/myclient.c -lm -pthread

myserver:
	$(CC) $(CFLAGS) -o $(BIN_DIR)/myserver $(SRC_DIR)/myserver.c

links:
	ln -sf $(BIN_DIR)/myclient myclient
	ln -sf $(BIN_DIR)/myserver myserver

clean:
	rm -rf $(BIN_DIR)/*
	rm -f myclient myserver
