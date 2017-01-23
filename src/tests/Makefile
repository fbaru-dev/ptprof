include ./common.mk

# Define the compiler
ifeq ($(COMPILER),GCC)
	CXX=g++
	CXXFLAGS+=-std=c++11 -fPIC
	CC=gcc 
	CFLAGS+=
	LDFLAGS= -fPIC -shared
endif

ifeq ($(COMPILER),ICC)
	CXX=icc
	CXXFLAGS+=-std=c++11 -fPIC
	CC=icpc
	CFLAGS+=
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

# Check if the library needs the C wrappers
ifeq ($(C_INTERFACE),true)
	
endif

#list of the target program names
EXE=ex1.x

#list of the examples to be compiled
SOURCES=example_1.cpp
##########################################
OBJS = $(SOURCES:.cpp=.o)
##########################################

#list of the lib to be linked against
LIBS = -L$(INST_LIB_DIR) -l$(LIBNAME)

#include files
INCLUDES = -I$(INST_INCLUDE_DIR)		

%.o: %.cpp
	$(info Compiling the test file: )
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ 


ex1.x: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LIBS) -o $(EXE)

clean:
	rm -f $(OBJS) *.x

run:
	./ex1.x

