CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = list_directory.h global_variables.h raw_input.h
OBJ = list_directory.o file_explorer.o global_variables.o raw_input.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

file_explorer: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
