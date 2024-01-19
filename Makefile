# All Targets
all: hello

# Tool invocations
# Executable "hello" depends on the files hello.o and run.o.

hello: clean bin/main.o bin/WareHouse.o
	@echo 'Building target: hello'
	@echo 'Invoking: C++ Linker'
	g++ -o bin/hello bin/WareHouse.o bin/main.o
	@echo 'Finished building target: hello'
	@echo ' '

# Depends on the source and header files
bin/WareHouse.o: src/WareHouse.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/WareHouse.o src/WareHouse.cpp


# Depends on the source and header files
bin/main.o: src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp

# Run the executable with command-line arguments
run: hello
	@echo 'Running target: hello'
	./bin/hello "/home/users/bsc/ossy/CPP/SPL-HW1/Example.txt"
	@echo ' '

#Clean the build directory
clean:
	rm -f bin/*