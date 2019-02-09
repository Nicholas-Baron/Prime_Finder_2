#ifndef _ASSERT_
#define _ASSERT_

#include <iostream>

#define assert(x) if(!(x)){ std::cerr << __FILE__ << '@' << __LINE__ << " : " << #x <<" failed!" << std::endl;}

#endif
