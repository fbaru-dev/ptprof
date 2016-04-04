# Configuration options setup

# supported: GCC, ICC (TODO)
COMPILER = GCC

# Installation directory, path where to install iptp 
INST_DIR=$(HOME)/ptptime-lib
LIB_DIR = $(INST_DIR)/lib
INCLUDE_DIR = $(INST_DIR)/include
EXAMPLE_DIR = $(INST_DIR)/examples

# Buid with PAPI instrumentation (TODO)
PAPI_INSTR = false
PAPI_HOME =

# Build C interface for the library (TODO)
C_INTERFACE = false

# Build iptp with debug flags
DEBUG = true

# Version and name of the library
VER:=.0.1
LIBNAME=libptp$(VER)
