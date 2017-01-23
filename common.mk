# Configuration options setup

# supported: GCC, ICC (TODO)
COMPILER = GCC

# Installation directory, path where to install ptprof library
WHERE = /home/hpc/pr28fa/di68xiw2/code/ptprof/install

#-------------------------------------------------------------
INST_DIR=$(WHERE)/ptprof-lib
INST_LIB_DIR = $(INST_DIR)/lib
INST_INCLUDE_DIR = $(INST_DIR)/include
INST_EXAMPLE_DIR = $(INST_DIR)/examples
INST_DOC_DIR = $(INST_DIR)/doc

# Build with PAPI instrumentation (TODO)
PAPI_INSTR = false
PAPI_HOME =

# Build C interface for the library (TODO)
C_INTERFACE = false

# Build ptprof lib with debug flags
DEBUG = true

# Version and name of the library
VER:=.0.1
LIBNAME=ptprof$(VER)
