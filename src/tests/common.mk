# Configuration options setup

# supported: GCC, ICC (TODO)
COMPILER = GCC

# Build ptplib example with debug flags
DEBUG = true

# Installation directory, path where to install iptp 
INST_DIR=$(HOME)/ptprof-lib
INST_LIB_DIR = $(INST_DIR)/lib
INST_INCLUDE_DIR = $(INST_DIR)/include
INST_EXAMPLE_DIR = $(INST_DIR)/examples
INST_DOC_DIR = $(INST_DIR)/doc

# Buid with PAPI instrumentation (TODO)
PAPI_INSTR = false
PAPI_HOME =

# Version and name of the library
VER:=.0.1
LIBNAME=ptprof$(VER)

