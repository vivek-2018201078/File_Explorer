CC = g++
CFLAGS = -Wall -std=c++1z -g
DEPS = list_directory.h global_variables.h raw_input.h command_mode.h command_exec.h file_copy.h copy_dir.h
OBJ = list_directory.o file_explorer.o global_variables.o raw_input.o command_mode.o command_exec.o file_copy.o copy_dir.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

file_explorer: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
