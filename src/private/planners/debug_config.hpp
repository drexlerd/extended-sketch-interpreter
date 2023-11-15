#ifndef DEBUG_CONFIG_H
#define DEBUG_CONFIG_H

#include <iostream>

#ifdef DEBUG
#define DEBUG_PRINT(x) std::cout << x << std::endl;
#else
#define DEBUG_PRINT(x)
#endif

#ifdef DEBUG
#define DEBUG_CODE(code) code
#else
#define DEBUG_CODE(code)
#endif

#endif // DEBUG_CONFIG_H
