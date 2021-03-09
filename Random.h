#ifndef RANDOMH
#define RANDOMH

#include <cstdlib>

inline double randomDouble()
{
    return rand () / (RAND_MAX + 1.0);
}
#endif