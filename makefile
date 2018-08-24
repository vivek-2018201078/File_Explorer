CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = list_directory.h
OBJ = list_directory.o file_explorer.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

file_explorer: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
