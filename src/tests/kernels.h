#define SIZE 20000

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

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
  int i;
  
  Cptprof *t;
  t = getInstance();
  
  for(i=0; i<SIZE; ++i) 
  {
    x[i] = sqrt((double) i * M_PI);
    y[i] = cos((double) i);
    res += x[i] * y[i];
    start(t,"compute");
      res = compute(res);
    stop(t);
  }
  return res;
}
