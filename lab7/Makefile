GCC = gcc

BUILD_DIR  = build
SOURCE_DIR = src

SERVER_NAME = server
CLIENT_NAME = client

all:
	$(GCC) -o $(BUILD_DIR)/$(SERVER_NAME) $(SOURCE_DIR)/server.c
	$(GCC) -o $(BUILD_DIR)/$(CLIENT_NAME) $(SOURCE_DIR)/client.c

client_run: $(BUILD_DIR)/$(CLIENT_NAME)
	$(BUILD_DIR)/$(CLIENT_NAME)

server_run: $(BUILD_DIR)/$(SERVER_NAME)
	$(BUILD_DIR)/$(SERVER_NAME)

clean:
	rm -rf build/*