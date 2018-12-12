#ifndef PARAMS_H_
#define PARAMS_H_

#define UNUSED __attribute__((unused))
#include <string>
#include "auxiliares.h"

class Params {
	public:
		Params(){};

		Params(int argc, char** argv) {
			if(argc == 4){
				opt1 = argv[3];
			}
		}

		bool opt1_as_bool(){
			return aux::to_bool(opt1);
		}

		int opt1_as_int(){
			return std::stoi(opt1);
		}

	private:
		std::string opt1;
};

#endif
