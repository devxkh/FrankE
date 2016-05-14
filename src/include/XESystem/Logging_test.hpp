
#include <iostream>
#include <sstream>

namespace XE
{
	void log(
		const char* argFile,
		int argLineNb,
		const char* argFunction,
		std::stringstream& argString) {
		std::cout << argFile << ":" << argLineNb << " " << argFunction
			<< " " << argString.str() << std::endl;
	}

}

#define XLOG(f) \
    do { std::stringstream s; \
         s << f; \
         XE::log(__FILE__, __LINE__, __FUNCTION__, s); \
    } while (0)
