#include "ptprof.hpp"

double Ptprof :: timelast = 0;
int Ptprof :: _initialize = 0;

Ptprof :: Ptprof()
{
  cout << "Initialization of the Ptprof lib without PAPI counters." << endl;
  _withpapi = 0;
  _countergroup = "no-counters";
    print_header();
  _time = new CPUWTime();
}

Ptprof :: Ptprof(string group_name)
{
  cout << "Initialization of the Ptprof lib." << endl;
  _countergroup = group_name;
  _withpapi = 1; 
    print_header();
  _time = new CPUWTime();
}


void Ptprof :: print_header()
{
  output << endl;
  output << "---------------------------------------------------------------" << endl;
  output << "------------------------- Ptprof Output ------------------------" << endl;
  output << "---------------------------------------------------------------" << endl;  
  output << left << setw(26) << "Regions" 
         << left << setw(14) << "ncalls"
         << left << setw(18) << "inc-wt(s) - (%)"
         << left << setw(18) << "exc-wt(s) - (%)"; 
	// if(_withpapi) {
// 	    for(int i=0; i < _papicount->getNumEvents(); ++i)
// 	    {
// 	      cout << right << setw(10) << _papicount->getNameEvents(i);
// 	    }
// 	}
  output << endl;
}
void Ptprof :: initialize(string context)
{
  if(!_initialize) {
    _initialize = 1;
    _context_name = context;
    lastname = "root";
    
    cout << "Open a context with name: " << _context_name << endl;
    
    _context_time = _time->getWcTime();
    
    if(_withpapi)
    {
      cout << "Starting with PAPI counter group: " << _countergroup << endl;
      _papicount = new PapiCount(_countergroup);
      _papicount -> papi_start();			//Start the PAPI counters
    }
    } else {
      cout << "ERR: Only one context at time allowed" << endl;
      abort();
    }
}

void Ptprof :: finalize()
{
  if(_initialize) {
    _initialize = 0;
    _context_time = _time->getWcTime() - _context_time;
    cout << "Close the context with name: " << _context_name << endl;
     
    print_context_data();
    clean_context_data();
    _context_time = 0.0;
    if(_withpapi)
    {
      /*TODO Papi stopping context */
      cout << "Stop with PAPI counter group: " << _countergroup << endl;
//       _papicount = new PapiCount(_countergroup);
//       _papicount -> papi_start();			//Start the PAPI counters
    }
  } else {
    cout << "ERR: Cannot finalize since there is no context opened" << endl; 
    abort();
  }
}

void Ptprof :: print_context_data()
{
  unsigned int i, j, k;
  vector<string> funcnameOutput(_funcsname);
  stringstream local_out, separator;     

  separator << setw(25) << setfill('-') << "-" 
            << setw(1)  << setfill(' ') << " "
            << setw(12) << setfill('-') << "-" 
            << "  "
            << setw(16) << setfill('-') << "-" 
            << "  "
            << setw(16) << setfill('-') << "-" 
	    << endl; 
  output << separator.str();

 //This part create the vector structure 'funcnameOutput' of the function calls according to
 //the label name which ends with tha letter 'F' which stays for 'final'
	   
  for(j=0; j < _funcsname.size(); ++j)
  {
  	string name = _funcsname[j];
	int size = name.size();
	string nametofind = name;
	nametofind.replace(size-1,size,"F");
	for(i=0; i < _funcsname.size(); ++i)
	{
		if(!nametofind.compare(_funcsname[i])) break;	
	}	
//         unsigned int n = i/2;
	for(k=j+1; k<i; ++k) { funcnameOutput[k].insert(0,"-"); } //Add some indent to identify the call stack in the
	   							      // output print
  }
  
  double timeexc_context=0.0;
  
  /* Print the information to the standard output */
  for (i=0; i < _funcsname.size(); ++i)
  {
      int  stringSize  = funcnameOutput[i].size();
      int  lastCharPos = stringSize - 1;
      char lastchar = funcnameOutput[i].at(lastCharPos);
      
      if(lastchar == 'I') 				//Remove the label 'I'
      {
        int ndash = count_dash(funcnameOutput[i]);
        string ss;
	ss.assign(ndash*2,' ');
        local_out << setw(26) << left << tree_name(funcnameOutput[i]) << ss;
     	local_out << setw(14) << left << _ncalls[_funcsname[i]]; 
        local_out << setw(6)  << left << setprecision(5) <<  _timeinc[_funcsname[i]];
	local_out << setw(4) << " - ("; 
	local_out << setw(4) << setprecision(3) << (_timeinc[_funcsname[i]]/_context_time)*100. << ")";
	local_out << setw(3) << setfill(' ') << " " ;
	local_out << setw(6) << left << setprecision(5) <<  _timeexc[_funcsname[i]];
	local_out << setw(4) << " - (";
	local_out << setw(4) << setprecision(3) << (_timeexc[_funcsname[i]]/_context_time)*100. << ")";
			
	    // if(_withpapi) {
// 		 for(int j=0; j <_papicount->getNumEvents(); ++j)
// 		 {
// 		   cout << right << setw(10) << _papivalues[_funcs[i]][j];
// 		 }
// 	    }
	timeexc_context += _timeexc[_funcsname[i]];     //Accumulate the total time of the context
	local_out << '\n';
      }
  }
  
  output << setw(26) << left << _context_name; 
  output << setw(14) << left << 1;
  output << setw(6)  << left << setprecision(5) << _context_time;
  output << setw(4) << " - (";
  output << setw(4) << setprecision(3) << (_context_time /_context_time)*100. << ")";
  output << setw(3) << setfill(' ') << " " ; 
  output << setw(6) << left << setprecision(5) <<  _context_time-timeexc_context;
  output << setw(4) << " - ("; 
  output << setw(4) << setprecision(3) << ((_context_time-timeexc_context)/_context_time)*100. << ")";
  output << '\n';	    		
  output << local_out.str();
  output << endl;
}

void Ptprof :: clean_context_data()
{
  _timeexc.clear();
  _timeinc.clear();
  _timecall.clear();
  _ncalls.clear();
  _funcsname.clear();
  while(!_stackfun.empty()) _stackfun.pop();
}

void Ptprof :: start(string name)
{
     unsigned int i;
     double timeon;
     string startname = name+"I";			//Name of the initial region (internally with the label 'I')
	
     if(_initialize) 
     {
	for (i=0; i < _funcsname.size(); ++i)		//Check if I need to create a new item in the function name vector
	{
		if(_funcsname[i].compare(startname) == 0) break;
	}
	
	if (i == _funcsname.size()) 
	{
	 //  cout << "Adding new start entry: " << startname << endl;
	  _funcsname.push_back(startname);
	  _ncalls[name]  = 0;
	  _timeinc[name] = 0;
	  _timeexc[name] = 0;	
	//  _cputick[name] = cputick;
	}
		
	_stackfun.push(startname); 			//Add the name to the function stack
	timeon = _time->getWcTime();			//Get the initial time
	
	_timecall[startname] = timeon;		
	_ncalls[startname] += 1;			//Update the number of calls
	
	if(_stackfun.size() > 1)       // If there is at least one element in the stack
	{
		//I want to compute the exclusive time for the region
		string temp = _stackfun.top();
		_stackfun.pop();
		_timeexc[_stackfun.top()] += (timeon - timelast);
		_stackfun.push(temp);
	}	
	timelast = timeon;
	lastname = name;
	
	_papicount -> papi_read();
	for(int j=0; j < _papicount->getNumEvents(); ++j)
	{
	  _papivalues[_funcsname[i]].push_back(_papicount->getValues(j));
	}
	
     } else {
       cout << "ERR: Cannot start a timing region: context not initialized" << endl;
       abort();
     }
}

void Ptprof :: stop()
{ 
    if(_initialize) 
     {
        double timeoff;
	unsigned int i;
	if( !_stackfun.empty() )
	{
	  string lastNameinStack = _stackfun.top();
	  string name = lastNameinStack.substr(0,lastNameinStack.length()-1); //The names have labels 
	
	  timeoff = _time->getWcTime();
	
	  string startname = name+"I";
	  string stopname  = name+"F";
	
	
	  for (i=0; i < _funcsname.size(); ++i)		//Check if I need to create a new item in the function name vector
	  {
	     if(_funcsname[i].compare(stopname) == 0) break;
	  }
	  if (i == _funcsname.size()) 
	  { 
	  //cout << "Adding new stop entry: " << stopname << endl;
	    _funcsname.push_back(stopname);
	  } 		

	//Take the upper region name time and remove from the exclusive time
	  _timeinc[startname] += (timeoff - _timecall[_stackfun.top()]);
	  _timeexc[startname] += (timeoff - timelast);
	
	  timelast = timeoff;
	
	  _stackfun.pop();		//Remove the last element from the stack
	  if(!_stackfun.empty()) {
	    lastname = _stackfun.top();
	  } else {
	    lastname = "root";
	  }
	  
	} else {
	  cout << "ERR: Number of start and stop not equal!" << endl;
	  abort();
	}
	
      } else {
	cout << "ERR: cannot stop a timing region: context not initialized" << endl;
	abort();
      }
	
	//_cputime[name].stop();
	//_cputick[name].stop();
	_papicount -> papi_read();
	
	for(int i=0; i < _papicount->getNumEvents(); ++i)
	{
	  long long truevalue = 0L;
	  long long value = _papicount->getValues(i);
	  cout << "HERE = " << " " << _funcsname[0] << " " << value << " " <<  _papivalues[_funcsname[0]][i] << endl;
	  truevalue = _papivalues[_funcsname[0]][i] - value;
	  _papivalues[_funcsname[0]][i] = truevalue;
	  cout << "HERE = " << " " << _funcsname[0] << " " << truevalue << endl;
	}
}

void Ptprof :: print()
{
	cout << output.str();
}

string Ptprof :: tree_name(string name) 
{
    int ndash = count_dash(name);
    string name_out;
    name_out = name.erase(0,ndash);
    name_out.insert(0,"|_ ");
    for(int i=0; i<ndash; ++i) name_out.insert(0,"  ");
    name_out = name_out.substr(0,name_out.size()-1);
    
    return name_out;
}

Ptprof :: ~Ptprof()
{
  delete _time;
  cout << "Delete CPUWTime " << endl;
  if(_withpapi) {
    delete _papicount;
    cout << "Delete PAPI " << endl;
  }
}
