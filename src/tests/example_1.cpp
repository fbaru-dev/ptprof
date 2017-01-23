#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <iostream>

#include "ptprof.hpp"
#include "kernels.hpp"

double kern1();

int main(int argc, char** argv) 
{
  double a,k;
  
  Ptprof *ttime;
    ttime = Ptprof::getInstance();
  
  ttime->initialize("context");
  sleep(1);
   
  ttime->start("kern1");    
  for(int i=0; i<1000; ++i) {
     a = kern1();
  }
  ttime->stop();
  std::cout << "a = " << a << std::endl;
  for(int i=0; i<1; ++i) {
   ttime->start("first");
    sleep(1);
   
   ttime->start("second");
    sleep(3);
    double b = kern1();
    std::cout << "b = " << b << std::endl;
   
   for(int i=0; i<1; ++i) {
    ttime->start("insert1");
     sleep(1);
    ttime->start("insert2");
     sleep(1);
    ttime->stop();
    ttime->start("kern2");
     k = kern2();
    ttime->stop(); 
         
    ttime->start("insert2.1");
     sleep(1);
    ttime->start("insert3.1");
    sleep(1);
    ttime->stop();
    ttime->stop();
    ttime->stop(); 
  }
       
  ttime->stop();
    
  sleep(1);
  
  ttime->start("third");
   sleep(3);
   double c = kern1();
  ttime->stop();
  std::cout << "c = " << c << std::endl;
  
  sleep(1);
  ttime->stop();
  
  }   
  ttime->finalize();

    ttime->initialize("another");
    ttime->start("fourth");
     sleep(1);
     ttime->start("kern1");
          a = kern1();
     ttime->stop();
    ttime->stop();
    sleep(2);
    
  ttime->finalize();
  
  ttime->print();

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


