CC = g++
CFLAGS = -std=c++11 -I lib/SFML-2.5.1/include
LDFLAGS = -L lib/SFML-2.5.1/lib
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRCS = $(wildcard src/*.cpp)
SRCS += src/main.cpp
OBJS = $(SRCS:src/%.cpp=build/%.o)

PROJECT_NAME = PowerPuff_Shooter
TARGET = build/$(PROJECT_NAME)

.PHONY: all clean copy run build

all: 
	@$(MAKE) build
	@echo
	@echo "------------------------------------------------------------------"
	@echo "			Copying File..."
	@echo "------------------------------------------------------------------"
	@$(MAKE) copy
	
	@echo
	@echo "------------------------------------------------------------------"
	@echo "			Running project..."
	@echo "------------------------------------------------------------------"
	@$(MAKE) run
	@echo "------------------------------------------------------------------"
	@echo "Build finished! Have a nice day!"

build:
	rm -f build/*.o build/*.exe
	@echo "			Creating build directory..."
	mkdir -p build
	@echo "------------------------------------------------------------------"
	@echo "			Building '$(PROJECT_NAME)'..."
	@echo "------------------------------------------------------------------"
	$(MAKE) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
	@echo
	@echo "project built..!"

clean:
	rm -rf build
	@echo
	@echo "project clean..!"

copy: $(TARGET)
	cp lib/SFML-2.5.1/bin/*.dll build
	@cp -rf src/assets build
	@echo
	@echo "Supported file copied..!"

run: $(TARGET)
	cd build && ./$(PROJECT_NAME)
	@echo
	@echo "Project finished running..!"