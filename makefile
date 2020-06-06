# makefile (ncurses)
# Dustin Walkup 

# Log file name
LOGC=log_compile
LOGL=log_link

# Executable name
EXEC=main

# Create the course code file list.  Expansion happens now.
SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.h)

# Create object file variable.  Expansion happens when variable is referenced
OBJECTS= *.o

# Compiler options
CC=g++
CFLAG=-v -c -g -std=c++11 -Wall 
LDLIBS=-lncurses -lmenu
# Make targets
all:		$(EXEC)

$(EXEC):
#	rm -f $(LOGC) $(LOGL)
	@$(CC) $(CFLAG) $(SOURCES) > $(LOGC) 2>&1
	@$(CC) -o main  $(OBJECTS) $(LDLIBS) #> $(LOGL) 2>&1 

compile:
	rm -f $(LOGC)
	@$(CC) $(CFLAG) $(SOURCES) > $(LOGC) 2>&1 

clean:	 
	@rm -f $(EXEC) $(LOGC) $(LOGL) $(patsubst %.cpp,%.o,$(wildcard *.cpp))

