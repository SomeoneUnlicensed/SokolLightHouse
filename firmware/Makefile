CC = aarch64-linux-musl-gcc
CXX = aarch64-linux-musl-g++
AS = aarch64-linux-musl-as
STRIP = aarch64-linux-musl-strip

CFLAGS = -O3 -march=armv8-a+crc -Wall
CXXFLAGS = -O3 -march=armv8-a+crc -Wall -std=c++11
LDFLAGS = -static

SRC_DIR = src
OBJ_DIR = build
BIN = sokol-lighthouse

OBJS = $(OBJ_DIR)/main.o \
       $(OBJ_DIR)/gnss.o \
       $(OBJ_DIR)/lora.o \
       $(OBJ_DIR)/crc16.o

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^
	$(STRIP) $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/crc16.o: $(SRC_DIR)/crc16.S
	@mkdir -p $(OBJ_DIR)
	$(AS) -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(BIN)

.PHONY: all clean
