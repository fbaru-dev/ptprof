#include "ptprof.hpp"
#include "ptprof_cwrapper.h"

extern "C" {

Cptprof * getInstance() {
       Ptprof *t;
       t = Ptprof::getInstance();

       return (Cptprof *)t;
}

void initialize(const Cptprof *test, char *name) {
	Ptprof *t = (Ptprof *)test;
	string my_string(name);
	t -> initialize(my_string);
}

void start(const Cptprof *test, char *name) {
	Ptprof *t = (Ptprof *)test;
	string my_string(name);
	t -> start(my_string);
}

void stop(const Cptprof *test) {
	Ptprof *t = (Ptprof *)test;
	t -> stop();
}

void finalize(const Cptprof *test) {
	Ptprof *t = (Ptprof *)test;
	t -> finalize();
}

void print(const Cptprof *test) {
	Ptprof *t = (Ptprof *)test;
	t -> print();
}


void cancel(const Cptprof *test) {
        Ptprof *t = (Ptprof *)test;
        delete t;
}

}