CC=gcc
CFLAGS=-Wall -g -pthread 
SRC_DIR=src

# Source files
MYCLIENT_SRC=$(SRC_DIR)/myclient.c
MYSERVER_SRC=$(SRC_DIR)/myserver.c

# Executables
MYCLIENT_EXE=myclient
MYSERVER_EXE=myserver

# Default target
all: $(MYCLIENT_EXE) $(MYSERVER_EXE)

# Compile myclient
$(MYCLIENT_EXE): $(MYCLIENT_SRC)
	$(CC) $(CFLAGS) -o $@ $<

# Compile myserver
$(MYSERVER_EXE): $(MYSERVER_SRC)
	$(CC) $(CFLAGS) -o $@ $<

# Clean target
clean:
	rm -f $(MYCLIENT_EXE) $(MYSERVER_EXE)

.PHONY: all clean
