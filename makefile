  
# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -Werror

# the build target executable:

all: task1 task2 task3

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(all) $(all).cpp

clean:
	$(RM) task1 task2 task3