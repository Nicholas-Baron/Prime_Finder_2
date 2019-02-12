#ifndef _ASSERT_
#define _ASSERT_

#include <iostream>

// My own assert function that uses std::cerr 
#define assert(x)\
if(!(x)){\
std::cerr << __FILE__ << '@' << __LINE__\
<< " : " << #x <<" failed!" << std::endl;\
}

#endif
