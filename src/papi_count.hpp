#ifndef _PAPICOUNT_HPP
#define _PAPICOUNT_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <stdlib.h>

#ifdef PAPILIB
#include <papi.h>
#endif

#ifndef PAPILIB
#define PAPI_NULL 0 
#endif

using namespace std;

class PapiCount {
private:
      static const int num_events = 3;
      static int event_set;
      static int _isinitialized;
      static int _isstarted;
      
      int              papi_events[num_events];
      string           name_events[num_events];
      long long             values[num_events];
      int _withcounters;
      
      string _countergroup;
      
      void init(string group);
      void set_events(string group);
      void papi_init();
      void papi_hwinfo();
      void papi_addevents();
public:
      PapiCount();
      PapiCount(string group);
      ~PapiCount();
      
      void papi_start();
      void papi_read();
      
      inline int getNumEvents() {return num_events;}
      inline string getNameGroup() {return _countergroup;}
      inline string getNameEvents(int i) {return name_events[i];}
      inline long long getValues(int i) {return values[i];}
    
};
#endif