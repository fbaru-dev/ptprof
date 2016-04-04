SRC_DIR = ./src
DOC_DIR = ./doc

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

TARGET=lib build_dir install info

all: $(TARGET)
#$(BUILD_DIR) $(LIBNAME) $(INSTALL) $(clean)

%.o: %.cpp
	$(info Compiling the object file: )
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ 
	
doc: 
	doxygen

distrib:
	git archive --format=tar --prefix=ptplib-$(VER)/ $(VER) | gzip > ../ptplib-$(VER).tar.gz

build_dir:
	mkdir -p $(INST_DIR) $(LIB_DIR) $(INCLUDE_DIR) $(EXAMPLE_DIR)
	
exe: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LIBS) -o $(EXE)

lib: $(OBJS)
	$(info Create the shared and static libs: )
	$(CXX) $(LDFLAGS) $(OBJS) $(LIBS) -o $(LIBNAME).so
	ar rc $(LIBNAME).a $(OBJS)

install:
	$(info Installation of the lib: )
	cp -p $(LIBNAME).a $(LIBNAME).so $(LIB_DIR)
	cp -p $(SRC_DIR)/*.hpp $(INCLUDE_DIR)
	cp -p $(SRC_DIR)/tests/*.cpp $(EXAMPLE_DIR)

info:
	$(info)
	$(info To test the library, go to the installation dir:)
	$(info $(LIB_DIR) )
	$(info and run "make")
	
clean:
	rm -f $(OBJS) *.so *.a

.PHONY: clean