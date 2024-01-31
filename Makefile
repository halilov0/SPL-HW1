# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
CC = g++
CFLAGS = -g -Wall -Weffc++ -std=c++11
LFLAGS = -L/usr/lib

# All Targets
all: hello

# Tool invocations
# Executable "hello" depends on the files hello.o and run.o.
hello: clean bin/AddCustomer.o bin/AddOrder.o bin/BaseAction.o bin/CollectorVolunteer.o bin/Customer.o bin/DataHandler.o bin/DriverVolunteer.o bin/main.o bin/Order.o bin/Printer.o bin/SimulateStep.o bin/Volunteer.o bin/WareHouse.o
	@echo 'Building target: hello'
	@echo 'Invoking: C++ Linker'
	$(CC) -o bin/hello bin/AddCustomer.o bin/AddOrder.o bin/BaseAction.o bin/CollectorVolunteer.o bin/Customer.o bin/DataHandler.o bin/DriverVolunteer.o bin/main.o bin/Order.o bin/Printer.o bin/SimulateStep.o bin/Volunteer.o bin/WareHouse.o $(LFLAGS)
	@echo 'Finished building target: hello'
	@echo ' '

# Depends on the source and header files
bin/AddCustomer.o: src/AddCustomer.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/AddCustomer.o src/AddCustomer.cpp

bin/AddOrder.o: src/AddOrder.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/AddOrder.o src/AddOrder.cpp

bin/BaseAction.o: src/BaseAction.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/BaseAction.o src/BaseAction.cpp

bin/CollectorVolunteer.o: src/CollectorVolunteer.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/CollectorVolunteer.o src/CollectorVolunteer.cpp

bin/Customer.o: src/Customer.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Customer.o src/Customer.cpp

bin/DataHandler.o: src/DataHandler.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/DataHandler.o src/DataHandler.cpp

bin/DriverVolunteer.o: src/DriverVolunteer.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/DriverVolunteer.o src/DriverVolunteer.cpp

bin/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/main.o src/main.cpp

bin/Order.o: src/Order.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Order.o src/Order.cpp

bin/Printer.o: src/Printer.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Printer.o src/Printer.cpp

bin/SimulateStep.o: src/SimulateStep.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/SimulateStep.o src/SimulateStep.cpp

bin/Volunteer.o: src/Volunteer.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Volunteer.o src/Volunteer.cpp

bin/WareHouse.o: src/WareHouse.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/WareHouse.o src/WareHouse.cpp


# Run the executable with command-line arguments
run: hello
	@echo 'Running target: hello'
	./bin/hello "/home/users/bsc/ossy/CPP/SPL-HW1/Example.txt"
	@echo ''

#Clean the build directory
clean:
	rm -f bin/*

