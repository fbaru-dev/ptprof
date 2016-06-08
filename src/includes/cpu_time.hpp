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

#ifndef _CPUWTIME_HPP
#define _CPUWTIME_HPP

#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>

// Return number of microseconds since 1.1.1970, in a 64 bit integer.

class CPUWTime {
private:
    double cputime, wctime;
    
    inline void readTime() 
    {
      struct timeval tp;
      struct rusage ruse;

      gettimeofday(&tp, NULL);
      wctime = (double) (tp.tv_sec + tp.tv_usec/1000000.0); 
  
      getrusage(RUSAGE_SELF, &ruse);
      cputime = (double)(ruse.ru_utime.tv_sec+ruse.ru_utime.tv_usec / 1000000.0);
    }
public:
    CPUWTime() : cputime(0.0), wctime(0.0) { }
    
    inline double getCpuTime() {readTime(); return cputime; }
    
    inline double getWcTime()  {readTime(); return wctime;}
    
};

#endif
