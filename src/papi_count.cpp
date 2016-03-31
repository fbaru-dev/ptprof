#include "papi_count.hpp"

/*
 * http://icl.cs.utk.edu/projects/papi/wiki/PAPITopics:SandyFlops
 * PRESET Event			Definition
 * -------------------------------------------------------------
 * PAPI_FP_INS 		SSE_SCALAR_DOUBLE + SSE_FP_SCALAR_SINGLE
 * PAPI_FP_OPS 		same as above
 * PAPI_SP_OPS 		FP_COMP_OPS_EXE:SSE_FP_SCALAR_SINGLE + 4*(FP_COMP_OPS_EXE:SSE_PACKED_SINGLE) + 8*(SIMD_FP_256:PACKED_SINGLE)
 * PAPI_DP_OPS 		FP_COMP_OPS_EXE:SSE_SCALAR_DOUBLE + 2*(FP_COMP_OPS_EXE:SSE_FP_PACKED_DOUBLE) + 4*(SIMD_FP_256:PACKED_DOUBLE)
 * PAPI_VEC_SP 		4*(FP_COMP_OPS_EXE:SSE_PACKED_SINGLE) + 8*(SIMD_FP_256:PACKED_SINGLE)
 * PAPI_VEC_DP 		2*(FP_COMP_OPS_EXE:SSE_FP_PACKED_DOUBLE) + 4*(SIMD_FP_256:PACKED_DOUBLE) 
*/

int PapiCount :: event_set = PAPI_NULL;
int PapiCount :: _isinitialized = 0;
int PapiCount :: _isstarted = 0;

PapiCount :: PapiCount()
{
  cout << "PapiCount :: PapiCount() " << endl;
  values[0] = 0LL; 
  values[1] = 0LL; 
  values[2] = 0LL;
  _countergroup = "";
  if(!_isinitialized) init(_countergroup);
}

PapiCount :: PapiCount(string group)
{
  cout << "PapiCount :: PapiCount(string group) " << endl;
  values[0] = 0LL; 
  values[1] = 0LL; 
  values[2] = 0LL;
  _countergroup = group;
  if(!_isinitialized) init(_countergroup);
}

void PapiCount :: init(string group)
{
#ifdef PAPILIB
  set_events(group);
  papi_init();
  papi_hwinfo();
  papi_addevents();
  _isinitialized = 1;
#else
  cout << "PapiCount not using the PAPI library!" << endl;
#endif
}

void PapiCount :: set_events(string group)
{
#ifdef PAPILIB
  if(!group.compare("default")) {
      _withcounters = 1;
      papi_events[0] = PAPI_TOT_INS;  name_events[0] = "PAPI_TOT_INS";
      papi_events[1] = PAPI_FP_INS;   name_events[1] = "PAPI_FP_INS";
      papi_events[2] = PAPI_TOT_CYC;  name_events[2] = "PAPI_TOT_CYC";
      cout << "Set PapiCount to defaults: " ; 
  } else if(!group.compare("flops-dp")) {
      _withcounters = 1;
      papi_events[0] = PAPI_FP_OPS;   name_events[0] = "PAPI_FP_OPS";
      papi_events[1] = PAPI_DP_OPS;   name_events[1] = "PAPI_DP_OPS";
      papi_events[2] = PAPI_VEC_DP;   name_events[2] = "PAPI_VEC_DP";
      cout << "Set PapiCount to flops-dp: "; 
  } else if(!group.compare("flops-sp")) {
      _withcounters = 1;
      papi_events[0] = PAPI_FP_OPS;   name_events[0] = "PAPI_FP_OPS";
      papi_events[1] = PAPI_SP_OPS;   name_events[1] = "PAPI_SP_OPS";
      papi_events[2] = PAPI_VEC_SP;   name_events[2] = "PAPI_VEC_SP";
      cout << "Set PapiCount to flops-sp: ";     
  } else if(!group.compare("memory")) {
      _withcounters = 1;
      papi_events[0] = PAPI_LD_INS;   name_events[0] = "PAPI_LD_INS";
      papi_events[1] = PAPI_SR_INS;   name_events[1] = "PAPI_SR_INS";
      papi_events[2] = PAPI_TOT_INS;  name_events[2] = "PAPI_TOT_INS";
      cout << "Set PapiCount to memory: "; 
  } else if(!group.compare("no-counters")) {
      cout << "Not using the PAPI counters" << endl;
      _withcounters = 0;
      papi_events[0] = 0; papi_events[1] = 0; papi_events[2] = 0;
      name_events[0] =""; name_events[1] =""; name_events[2] ="";
  } else {
      _withcounters = 1;
      cout << "No group found to PapiCount: set to defaults" << endl;
      papi_events[0] = PAPI_TOT_INS;  name_events[0] = "PAPI_TOT_INS";
      papi_events[1] = PAPI_FP_INS;   name_events[1] = "PAPI_FP_INS";
      papi_events[2] = PAPI_TOT_CYC;  name_events[2] = "PAPI_TOT_CYC";
      cout << "Set PapiCount to defaults: " ; 
  }
  if(_withcounters) {
    cout << "{" << name_events[0] << "," << name_events[1] << "," << name_events[2] << "}" << endl;
  }
#endif
}

void PapiCount :: papi_init() 
{
#ifdef PAPILIB  
    int retval;
    int num_hwcntrs=0; 
    
    if(_withcounters) {
   /* Initialize the PAPI library and get the number of counters available */
      if((retval = PAPI_library_init(PAPI_VER_CURRENT)) != PAPI_VER_CURRENT ) {
        cerr << "PapiCount::papi_init() " << __FILE__ << " " <<  __LINE__ << " " 
             << "PAPI_library_init(" << PAPI_VER_CURRENT << ") = " << PAPI_strerror(retval) << endl;
        exit(1);
      }
    
      if((num_hwcntrs = PAPI_num_counters()) <= PAPI_OK) {  
        cerr << "PapiCount::papi_init() " << __FILE__ << " " <<  __LINE__ << " " 
             << "PAPI_num_counters() = " << num_hwcntrs << endl;
        exit(1);
      } else {
        cout << "This system has " <<  num_hwcntrs << " available counters. We set only " << num_events << "." << endl;
      }
    }
#endif  
}

void PapiCount :: papi_hwinfo()
{
#ifdef PAPILIB
  const PAPI_hw_info_t *hwinfo = NULL;
  
  if(_withcounters) {
    if((hwinfo = PAPI_get_hardware_info()) <= PAPI_OK ) {
        cerr << "PapiCount::papi_hwinfo() " << __FILE__ << " " <<  __LINE__ << " " 
             << "PAPI_get_hardware_info()" << endl;
        exit(1);
      }
   
   cout << "---------------------------------------------------------------" << endl;
   cout << "------------------ CPU Informations ---------------------------" << endl;
   cout << "---------------------------------------------------------------" << endl;
   cout << setw(32) << left << hwinfo->model_string << endl;
   cout << setw(32) << left << "Number of NUMA nodes" << right << ":" << setw(10) << hwinfo->nnodes << endl;
   cout << setw(32) << left << "Number of Sockets" << right << ":" << setw(10) << hwinfo->sockets<< endl;
   cout << setw(32) << left << "Number of Cores per socket" << right << ":" << setw(10) << hwinfo->cores << endl;
   cout << setw(32) << left << "Number of CPUs per NUMA Node" << right << ":" << setw(10) << hwinfo->ncpu << endl;
   cout << setw(32) << left << "Number of total CPUs" << right << ":" << setw(10) << hwinfo->totalcpus << endl;
   cout << setw(32) << left << "CPU Max Megahertz" << right << ":" << setw(10) << hwinfo->cpu_max_mhz << endl;
   cout << setw(32) << left << "CPU Min Megahertz" << right << ":" << setw(10) << hwinfo->cpu_min_mhz << endl;
   cout << setw(32) << left << "Hdw Threads per core" << right << ":" << setw(10) << hwinfo->threads << endl;
   cout << "---------------------------------------------------------------" << endl;
   cout << "---------------------------------------------------------------" << endl;
  }
#endif
}

void PapiCount :: papi_addevents() 
{
#ifdef PAPILIB  
    int retval;
    
    if(_withcounters) {
    /* Check counters availability and add events*/
       if((retval = PAPI_create_eventset(&event_set)) != PAPI_OK) {
        cerr << "PapiCount::papi_addevents() " << __FILE__ << " " <<  __LINE__ << " " 
             << "PAPI_create_eventset() = " << PAPI_strerror(retval) << endl;
        exit(1);
      }
    
      for(int i=0; i < num_events; ++i) {
        if((retval = PAPI_query_event (papi_events[i])) != PAPI_OK) {
	  cerr << "PapiCount::papi_addevents() " << __FILE__ << " " <<  __LINE__ << " " 
               << "PAPI_query_event(" << name_events[i] << ") = " << PAPI_strerror(retval) << endl;
	  exit(1);
        }
      } 
    
      if((retval = PAPI_add_events (event_set, papi_events, num_events)) != PAPI_OK) {
        cerr << "PapiCount::papi_addevents() " << __FILE__ << " " <<  __LINE__ << " " 
             << "PAPI_add_events(event_set, ... ) = " << PAPI_strerror(retval) << endl;	
	exit(1);
      } else {
        cout << "PapiCount::papi_addevents() events: " 
	     << "{" << name_events[0] << "," << name_events[1] << "," << name_events[2] << "}" << " set." << endl;
      }
    }
#endif  
}

void PapiCount :: papi_start() 
{
#ifdef PAPILIB  
    int retval;
    
    if(_withcounters && !(_isstarted)) {
    /* Start counting events */
      if ((retval = PAPI_start(event_set)) != PAPI_OK) {
	  cerr << "PapiCount::papi_start() " << __FILE__ << " " <<  __LINE__ << " " 
               << "PAPI_start(...) = " << PAPI_strerror(retval) << endl;
	  exit(1);
      }
//     if ((retval = PAPI_start_counters(papi_events, num_events)) != PAPI_OK) {
// 	cerr << "PapiCount::papi_start() " << __FILE__ << " " <<  __LINE__ << " " 
//              << "PAPI_start_counters(...) = " << PAPI_strerror(retval) << endl;
//     }
      _isstarted = 1;
    }
#endif
}

void PapiCount :: papi_read() 
{
#ifdef PAPILIB  
    int retval;
    
    if(_withcounters) {
    /* Read counting events */
      if ((retval = PAPI_read(event_set, values)) != PAPI_OK) {
	  cerr << "PapiCount::papi_read() " << __FILE__ << " " <<  __LINE__ << " " 
               << "PAPI_read(event_set, ...) = " << PAPI_strerror(retval) << endl;
	  exit(1);
      }
    }
#endif
}

PapiCount :: ~PapiCount()
{
  cout << "PapiCount :: ~PapiCount() " << endl;
#ifdef PAPILIB  
    int retval;
    
    if(_withcounters) {
    /* Stop counting events */
      if ((retval = PAPI_stop(event_set, values)) != PAPI_OK) {
	  cerr << "PapiCount::papi_stop() " << __FILE__ << " " <<  __LINE__ << " " 
               << "PAPI_stop(event_set) = " << PAPI_strerror(retval) << endl;
	  exit(1);
      }
    }
#endif
}

