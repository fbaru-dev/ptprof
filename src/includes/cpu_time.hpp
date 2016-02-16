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