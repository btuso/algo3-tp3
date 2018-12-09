#ifndef PARAMS_H_
#define PARAMS_H_

#define UNUSED __attribute__((unused))
#include <string>

struct Params {
	const string TRUE = "true";
	bool opt1 = false;

	Params(){};

	Params(int argc, char** argv) {
		if(argc == 4){
			if(TRUE.compare(argv[3]) == 0){
				opt1 = true;
			}
		}
	}
};

#endif
