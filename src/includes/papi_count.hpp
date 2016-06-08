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
