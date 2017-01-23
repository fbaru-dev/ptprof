include ./common.mk

# Define the compiler
ifeq ($(COMPILER),GCC)
	CC=gcc
	CFLAGS+=-Wall -Werror -g -ansi -pedantic -std=c99
	CXX=g++
	CXXFLAGS+=-std=c++11
endif

ifeq ($(COMPILER),ICC)
	CC=icc
	CFLAGS+=-Wall -Werror -g -ansi -pedantic -std=c99
	CXX=icpc
	CXXFLAGS+=-std=c++11
endif

# Check for the debug mode
ifeq ($(DEBUG),true)
	CXXFLAGS+= -g -Wall -pedantic
	CFLAGS+= -g -Wall -pedantic
else
	CXXFLAGS+= -O2
	CFLAGS+= -O2
endif	

# Check if the examples run with papi
ifeq ($(PAPI_INSTR),true)
	INCLUDES += $(PAPI_HOME)/include
	LIBS += $(PAPI_HOME)/lib
endif

#list of the target program names
all: ex1.x ex2.x 

#list of the examples to be compiled
SOURCECPP=example_1.cpp
SOURCEC=example_2.c
##########################################
OBJSCPP = $(SOURCECPP:.cpp=.o)
OBJSC   = $(SOURCEC:.c=.o)
##########################################

#list of the lib to be linked against
LIBS = -L$(INST_LIB_DIR) -l$(LIBNAME)

#include files
INCLUDES = -I$(INST_INCLUDE_DIR)		

%.o: %.cpp
	$(info Compiling the example_1 file: )
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ 

%.o: %.c
	$(info Compiling the example_2 file: )
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

ex1.x: $(OBJSCPP)
	$(CXX) $(CXXFLAGS) $(OBJSCPP) $(LIBS) -o ex1.x
	
ex2.x: $(OBJSC)
	$(CC) $(CFLAGS) $(OBJSC) $(LIBS) -o ex2.x

clean:
	rm -f *.o *.x

