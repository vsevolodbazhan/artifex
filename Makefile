APP_NAME = artifex

BUILD_DIR = build

CPP = g++
CFLAGS = -Wall -Ofast -std=c++17

DEPS = -lsfml-graphics -lsfml-window -lsfml-system

build:
	$(CPP) -c $(CFLAGS) $(APP_NAME).cpp -o $(BUILD_DIR)/$(APP_NAME).o
	$(CPP) $(BUILD_DIR)/$(APP_NAME).o -o $(BUILD_DIR)/$(APP_NAME) $(DEPS)

.PHONY: build
