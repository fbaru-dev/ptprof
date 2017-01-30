# Configuration options setup

# supported: GCC, ICC
COMPILER = ICC

# Installation directory, path where to install ptprof library
WHERE = $(HOME)/code/ptprof
#-------------------------------------------------------------
INST_DIR=$(WHERE)/ptprof-lib
INST_LIB_DIR = $(INST_DIR)/lib
INST_INCLUDE_DIR = $(INST_DIR)/include
INST_EXAMPLE_DIR = $(INST_DIR)/examples
INST_DOC_DIR = $(INST_DIR)/doc

# Build with PAPI instrumentation (TODO)
PAPI_INSTR = false
PAPI_HOME =

# Build ptprof lib with debug flags
DEBUG = false

# Version and name of the library
VER:=.1.0
LIBNAME=ptprof$(VER)

