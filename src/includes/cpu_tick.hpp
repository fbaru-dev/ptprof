/*
    This file is part of the library ptproc, a C++ performance timing library 
    which can also read hardware performance counters via PAPI library.
    
    Copyright (C) 2016  Fabio Baruffa <fbaru-dev@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CPUTICK_HPP
#define _CPUTICK_HPP

#include <stdint.h>

//This function gives the number of cycles
static __inline__ uint64_t rdtsc(void)
{
        uint64_t rval;
        __asm__ volatile ("rdtsc" : "=A" (rval));
        return rval;
}

static __inline__ unsigned long long startRDTSC (void) {
    unsigned cycles_low, cycles_high;
    asm volatile ("CPUID\n\t"
            "RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
            "%rax", "%rbx", "%rcx", "%rdx");
    return (static_cast<unsigned long long>(cycles_high) << 32) | cycles_low;
}

static __inline__ unsigned long long stopRDTSCP (void) {
    unsigned cycles_low, cycles_high;
    asm volatile("RDTSCP\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "CPUID\n\t": "=r" (cycles_high), "=r" (cycles_low):: "%rax",
            "%rbx", "%rcx", "%rdx");
    return (static_cast<unsigned long long>(cycles_high) << 32) | cycles_low;
}

class CPUTick {
private:
    unsigned long long ticktimestart;
    unsigned long long ticktimestop;
    unsigned long long ticktimetotal;
public:
    CPUTick() : ticktimestart(0), ticktimetotal(0) { }

    inline void start() {
        ticktimestart = startRDTSC();
    }
    
    inline void stop() {
        ticktimestop  = stopRDTSCP();
		ticktimetotal = ticktimestop - ticktimestart;
    }
    
    inline unsigned long long getTickTime() {
        return ticktimetotal;
    }
};
#endif
