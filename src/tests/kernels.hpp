#include "ptprof.hpp"

#define SIZE 20000

double compute(double a)
{
  double c=0.;
  if (a > 11.0) {
    c = log2(a);
  } else {
    c = exp2(a);
  }
  return c;
}

double kern2()
{
  double x[SIZE];
  double y[SIZE];
  double res = 0.;
  
  Ptprof *tlocal;
  tlocal = Ptprof::getInstance();
  
  for(int i=0; i<SIZE; ++i) 
  {
    x[i] = sqrt((double) i * M_PI);
    y[i] = cos((double) i);
    res += x[i] * y[i];
    tlocal->start("compute");
      res = compute(res);
    tlocal->stop();
  }
  return res;
}
