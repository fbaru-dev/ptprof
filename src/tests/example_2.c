#include <stdio.h>
#include <unistd.h>
#include <math.h>

#include "ptprof_cwrapper.h"
#include "kernels.h"

double kern1();

int main() 
{
  double a,b,c,k;
  
  Cptprof *t = NULL;
  t = getInstance();
   
  initialize(t,"context");
  sleep(1);	
   
  start(t,"kern1");    
  for(int i=0; i<1000; ++i) {
     a = kern1();
  }
  stop(t);
  printf("a = %e\n", a);
  for(int i=0; i<1; ++i) {
   start(t,"first");  
    sleep(1);
   
   start(t,"second");  
    sleep(3);
    b = kern1();
    printf("b = %e\n", b);
   
   for(int i=0; i<1; ++i) {
    start(t,"insert1");  
     sleep(1);
    start(t,"insert2");  
     sleep(1);
    stop(t);
    start(t,"kern2");  
     k = kern2();
    stop(t);
         
    start(t,"insert2.1");  
     sleep(1);
    start(t,"insert3.1");  
    sleep(1);
    stop(t);
    stop(t);
    stop(t); 
  }
  printf("k = %f\n", k);     
  stop(t);
    
  sleep(1);
  
  start(t,"third");  
   sleep(3);
   c = kern1();
  stop(t);
  printf("c = %e\n", c);
  
  sleep(1);
  stop(t);
  
  }   
  finalize(t);

    initialize(t,"another");
    start(t,"fourth");
     sleep(1);
     start(t,"kern1");
       a = kern1();
     stop(t);
    stop(t);
    sleep(2);
    
  finalize(t);
  
  print(t);
  cancel(t);
  t = NULL;
  
  return 0;

}

double kern1()
{
  double x[SIZE];
  double y[SIZE];
  double res = 0.;
  for(int i=0; i<SIZE; ++i) 
  {
    x[i] = sin((double) i * M_PI);
    y[i] = cos((double) i);
    res += x[i] * y[i];
  }
  return res;
}