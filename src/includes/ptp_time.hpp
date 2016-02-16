#ifndef _PTIME_HPP
#define _PTIME_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>			//ostringstream
#include <algorithm>			//count

#include "CPUWTime.hpp"
#include "CPUTick.hpp"
#include "PapiCount.hpp"

using namespace std;

//! PTime class. 
/*! This class includes all the profiling informations which can be
 * monitored and measured for the application you are going
 * to investigate.
*/

//This class could be a Singleton

class PTime {
private:
 	map<string,double>  		   _timeexc;	/**< std::map containing as key the name of the region
							      and value the exclusive time.*/
 	map<string,double>  		   _timeinc;    /**< std::map containing as key the name of the region
							      and value the inclusive time.*/
 	map<string,double>  		   _timecall;	/**< std::map containing as key the name of the region
							      and value the time for last call.*/
	map<string,unsigned long long>     _cputick;    /**< std::map containing as key the name of the region
							      and value the tick clock. */
	map<string,vector<long long> > 	   _papivalues; /**< std::map containing as key the name of the region
							      and value a std::vector which the values of There
							      PAPI counters. */
	
	map<string, unsigned int> 	   _ncalls;	/**< std::map containing as key the name of the region
							      and the number of calls */
	
	PapiCount* _papicount;				/**< pointer to the PapiCount class */ 
	CPUWTime*   _time;				/**< pointer to the CPUWTime class */ 
	
	vector<string> 	     _funcsname;		/**< std::vector of region names*/ 
	stack<string>        _stackfun;			/**< std::stack of the called regions*/
			
	static double timelast;				/**< time which takes the last call of the getWcTime() function in 
							     CPUWTime class.*/

	string lastname;				/**< last name used in the stack call.*/ 
	
	int 	_withpapi;				/**< flags which tells if the tool uses the PAPI counters*/ 
	string 	_countergroup;				/**< name of the counter region given in the constructor of
							     this class */ 
	
	string _context_name;				/**< name of the context which initializes the region
							     to profile with the tool */
	double _context_time;				/**< time between the initialize of the context and There
							     finalization */
	static int _initialize;				/**< flag which is use to check if the context has been initialized */
	stringstream 	 output;			/**< output string stream with the informations of the profiling */
	
        void print_header();				
	void print_context_data();
	void clean_context_data();
	
	string tree_name(string name); 			
	inline int count_dash(string name) 			
	{return count(name.begin(), name.end(), '-');}
	
public:
//! Default constructor
/*! Initializes the PTime class with the default constructor
*/ 
	PTime();
//! Constructor which takes a string argument
/*! This constructor takes a string as input. The string tells
 * you which category of PAPI measurements are taken
 * \param group_name a \b std:string argument of the group of PAPI counters.
 * There are 5 different groups (for more details see the documentation of the \ref PapiCount.hpp of the PapiCount class).
 * \param group_name are:
 * - \b default : set the default counters
 * - \b flops-dp : double precision floating points counters
 * - \b flops-sp : single precision floating points counters
 * - \b memory   : memory counters
 * - \b no-counters : not using any counter
 */	
	PTime(string group_name);
//! Default destructor
/*! Default destructor of the class
 */
	~PTime();
//! Initialization function
/*! This public function takes a \b std:string name for the context to profile.
 *  All the output data are refered to this initial point
 * 
 * \param context string name
 */
	void initialize(string context);
//! Finalization function
/*!
The function does not take any input paramentes. It closes the context and analyze the data.
 */	
	void finalize();
//! The public function which starts the profiling region
/*!
\param name string argument of the region we want to profile.
*/	
	void start(string name);
//! The public function which stops the profiling region
/*! 
The function does not take any input paramentes. It closes the latest profiling region in the stack.
*/
	void stop();
//! The public function which prints the profiling results
	void print();	
};
#endif