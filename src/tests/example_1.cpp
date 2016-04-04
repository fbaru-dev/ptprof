#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "cpu_tick.hpp"
#include "ptp_time.hpp"
#include "papi_count.hpp"

#include <unistd.h>
using namespace std;

int main(int argc, char** argv) 
{
   if(argc!=2) 
   {
      printf("usage: %s <num>\n", argv[0]);
      printf("number of operations: <num> millions\n");
      exit(EXIT_FAILURE);
   }
   
   int n=atoi(argv[1])*1000000;
   if(n<=0) n=10000;

   double x=M_PI;
   double y=1.0+1e-8;
   double giga=1e9;

   //PapiCount papi("flops-dp");
   PTime *ttime;
   
   ttime = new PTime("no-counters");
   
   ttime->initialize("context");
       sleep(1);
       ttime->start("first");    
    for(int i=0; i<1000; ++i) {
//       x=addmul(x,y,n);
    }
    ttime->stop();
//     ttime->finalize();
   for(int i=0; i<1; ++i) {
   ttime->start("first");
  // papi.papi_start();
   // x=addmul(x,y,n);
  // papi.papi_stop();
    //x=addmul(x,y,n);
   // papi.papi_start();
    //x=addmul(x,y,n);
    //papi.papi_stop();
    sleep(1);
    
    ttime->start("second");
     sleep(3);
//      x=addmul(x,y,n);
     for(int i=0; i<1; ++i) {
       ttime->start("insert1");
       sleep(1);
         ttime->start("insert2");
       		sleep(1);
	 ttime->stop();
	 
       	ttime->start("insert3");
       	       sleep(1);
         ttime->stop(); 
         
         ttime->start("insert2.1");
       		sleep(1);
       		ttime->start("insert3.1");
       		sleep(1);
            ttime->stop();
         ttime->stop();
       ttime->stop(); }
       
    ttime->stop();
    
    sleep(1);
  
    ttime->start("third");
     sleep(3);
    // x=addmul(x,y,n);
    ttime->stop();
    
      sleep(1);
      
     ttime->stop();
   }   
    ttime->finalize();

    ttime->initialize("another");
    ttime->start("fourth");
     sleep(1);
      ttime->start("addmul");
//        x=addmul(x,y,n);
       ttime->stop();
    ttime->stop();
    sleep(2);
ttime->finalize();
    
   ttime->print();
   
  
// cout << "SIZE = " << ftimings_resident_set_size() << endl;
//    printf("addmul:\t %.3f s, \t %.3f s, %.3f Gflops, res=%f\n",time.getCpuTime(),time.getWcTime(),((double)n/time.getWcTime())/giga,x);
	
   delete ttime;
    x=M_PI;
    y=1.0+1e-8;
    CPUTick cycle;
    cycle.start();
//     x=addmul(x,y,n);
    cycle.stop();
	
    printf("addmul:\t %.3f  cycles per ops, res=%f\n",(cycle.getTickTime()*1.0)/n,x);

    return EXIT_SUCCESS;
}