SRC_DIR = ./src
DOC_DIR = ./doc
LIB_DIR = ./lib
TEST_DIR = ./src/tests

include ./common.mk

# Define the compiler
ifeq ($(COMPILER),GCC)
	CC=gcc
	CFLAGS+=
	CXX=g++
	CXXFLAGS = -std=c++11 -fPIC 
	LDFLAGS  = -shared
	OPENMP   = -openmp 
endif

ifeq ($(COMPILER),ICC)
	CC=icc
	CFLAGS=
	CXX=icpc
	CXXFLAGS = -std=c++11 -fPIC 
	LDFLAGS  = -shared
	OPENMP   = -qopenmp 
endif

# Check for the debug mode
ifeq ($(DEBUG),true)
	CXXFLAGS+= -g -Wall -pedantic
	CFLAGS+= -g -Wall -pedantic
else
	CXXFLAGS+= -O3
	CFLAGS+= -O3
endif	

# Check if the library needs to be installed with PAPI
ifeq ($(PAPI_INSTR),true)
	INCLUDES += $(PAPI_HOME)/include
	LIBS += $(PAPI_HOME)/lib
endif


#include files
INCLUDES = -I$(SRC_DIR)/includes

#list of the files to be compiled
SOURCES=$(SRC_DIR)/ptprof.cpp $(SRC_DIR)/papi_count.cpp $(SRC_DIR)/wrapper/ptprof_cwrapper.cpp

##########################################
OBJS = $(SOURCES:.cpp=.o)
##########################################

all: lib

%.o: %.cpp
	$(info )
	$(info Compiling the object file: )
	$(CXX) $(CXXFLAGS) $(OPENMP) $(INCLUDES) -c $< -o $@ 
	
doc: 
	doxygen
#This should work is I use tas in the git repo
#distrib:
#	git archive --format=tar.gz --prefix=ptplib$(VER)/ v$(VER) >ptplib$(VER).tar.gz
	
exe: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OPENMP) $(OBJS) $(LIBS) -o $(EXE)

lib: $(OBJS)
	$(info )
	$(info Create the shared and static libs: )
	$(CXX) $(LDFLAGS) $(OBJS) $(LIBS) -Wl,-soname,lib$(LIBNAME).so -o lib$(LIBNAME).so
	ar rc lib$(LIBNAME).a $(OBJS)
	mv lib$(LIBNAME).a lib$(LIBNAME).so $(LIB_DIR) 
	

install: build_dir copy info

build_dir:
	$(info ) 
	$(info Create the installation directories: )
	mkdir -p $(INST_DIR) 
	mkdir -p $(INST_LIB_DIR) 
	mkdir -p $(INST_INCLUDE_DIR) 
	mkdir -p $(INST_EXAMPLE_DIR) 
	mkdir -p $(INST_DOC_DIR)

copy:
	$(info ) 
	$(info Installation of the lib: )
	cp -p $(LIB_DIR)/lib$(LIBNAME).a $(LIB_DIR)/lib$(LIBNAME).so $(INST_LIB_DIR)
	cp -p $(SRC_DIR)/includes/*.hpp $(INST_INCLUDE_DIR)
	cp -p $(SRC_DIR)/wrapper/*.h $(INST_INCLUDE_DIR)
	cp -p $(DOC_DIR)/* $(INST_DOC_DIR)
	cp -p $(TEST_DIR)/* $(INST_EXAMPLE_DIR)

info:

	$(info )
	$(info To test the library, go to the installation dir:)
	$(info $(INST_EXAMPLE_DIR) )
	$(info and run "make")
	
clean:
	rm -f $(OBJS) $(LIB_DIR)/lib$(LIBNAME)*

.PHONY: clean
