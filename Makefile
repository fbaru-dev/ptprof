SRC_DIR = ./src
DOC_DIR = ./doc

include ./common.mk

# Define the compiler
ifeq ($(COMPILER),GCC)
	CXX=g++
	CXXFLAGS+=-std=c++11 -fPIC
	CC=gcc 
	CFLAGS+=
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
SOURCES=PTime.cpp PapiCount.cpp example.cpp

##########################################
OBJS = $(SOURCES:.cpp=.o)
##########################################
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ 
	

all: $(BUILD_DIR) $(LIBNAME) $(INSTALL) $(clean)
			
doc: 
	doxygen

distrib:
	git archive --format=tar --prefix=ptplib-$(VER)/ $(VER) | gzip > ../ptplib-$(VER).tar.gz

$(BUILD_DIR):
	mkdir -p $(INST_DIR) $(LIB_DIR) $(INCLUDE_DIR) $(EXAMPLE_DIR)
	
$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LIBS) -o $(EXE)

$(LIBNAME): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LIBS) -o $@.so
	ar rc $@.a $(OBJS)

$(INSTALL):
	mv $(LIBNAME).a $(LIBNAME).so $(LIB_DIR)
	mv $(*.hpp) $(INCLUDE_DIR)
	mv $(EXE) $(EXAMPLE_DIR)

clean:
	rm -f $(OBJS)

.PHONY: clean