SRC_DIR = ./src
DOC_DIR = ./doc
LIB_DIR = ./lib

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

# Check if the library needs to be installed with PAPI
ifeq ($(PAPI_INSTR),true)
	INCLUDES += $(PAPI_HOME)/include
	LIBS += $(PAPI_HOME)/lib
endif

# Check if the library needs the C wrappers
ifeq ($(C_INTERFACE),true)
	
endif


#list of the files to be compiled
SOURCES=$(SRC_DIR)/ptp_time.cpp $(SRC_DIR)/papi_count.cpp

##########################################
OBJS = $(SOURCES:.cpp=.o)
##########################################

all: lib

%.o: %.cpp
	$(info Compiling the object file: )
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ 
	
doc: 
	doxygen
#This should work is I use tas in the git repo
#distrib:
#	git archive --format=tar.gz --prefix=ptplib$(VER)/ v$(VER) >ptplib$(VER).tar.gz
	
exe: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LIBS) -o $(EXE)

lib: $(OBJS)
	$(info Create the shared and static libs: )
	$(CXX) $(LDFLAGS) $(OBJS) $(LIBS) -o $(LIBNAME).so
	ar rc $(LIBNAME).a $(OBJS)
	mv $(LIBNAME).a $(LIBNAME).so $(LIB_DIR) 

install: build_dir copy info

build_dir:
	mkdir -p $(INST_DIR) $(INST_LIB_DIR) $(INST_INCLUDE_DIR) $(INST_EXAMPLE_DIR) $(INST_DOC_DIR)

copy:
	$(info Installation of the lib: )
	cp -p $(LIB_DIR)/$(LIBNAME).a $(LIB_DIR)/$(LIBNAME).so $(INST_LIB_DIR)
	cp -p $(SRC_DIR)/*.hpp $(INST_INCLUDE_DIR)
	cp -p $(SRC_DIR)/tests/*.cpp $(INST_EXAMPLE_DIR)
	cp -p $(DOC_DIR)/* $(INST_DOC_DIR)

info:
	$(info)
	$(info To test the library, go to the installation dir:)
	$(info $(INST_LIB_DIR) )
	$(info and run "make")
	
clean:
	rm -f $(OBJS) $(LIB_DIR)/$(LIBNAME)*

.PHONY: clean
