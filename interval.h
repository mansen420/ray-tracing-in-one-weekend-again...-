#ifndef INTERVAL
#define INTERVAL

#include "global_constants.h"

struct interval 
{
    const float min, max;
    interval () : min(+INF), max(-INF) {}
    interval (const float min, const float max) : min(min), max(max) {}
    bool contains_incl (float x) {return x >= min && x <= max;}
    bool contains_excl (float x) {return x > min && x < max;}
};

#endif