# Ptprof timing library and performance counters reading using PAPI

This repository contains a C++ timing library used to time different portions of a C++ code. It 
prints out the timing for each reagion which has been created in a context and can be read performance counter
using the library PAPI (http://icl.utk.edu/papi/)

## Build

To build the library, edit the `common.mk` file to specify which is your favourable directory to use as installation
directory for the library and the examples.
Then it is usually enough to call `make`:

    $> make

If you run into issues, have a look at `Makefile` and adjust compilers, etc.

## Install

It is enough to run `make install` to copy all the necessary files to the installation directory you have provided in the `common.mk` file. 

## Run

Go to the installation directory and compile the examples.

    $> make
  
Then for the C++ example:

    $> ./ex1.x

for the C example:

    $> ./ex2.x
     
In case you have problem due to the shared library, please export the environment variable `LD_LIBRARY_PATH`:

    $> export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/your/installation/directory

## Examples

## License

See file LICENSE for details.


