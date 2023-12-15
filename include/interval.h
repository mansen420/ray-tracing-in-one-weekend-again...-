#ifndef INTERVAL
#define INTERVAL

#include <limits>

constexpr float INF = std::numeric_limits<float>::infinity();

struct interval 
{
    const float min, max;
    interval () : min(+INF), max(-INF) {}
    interval (const float min, const float max) : min(min), max(max) {}
    bool contains_incl (const float x) const {return x >= min && x <= max;}
    bool contains_excl (const float x) const {return x > min && x < max;}
    float clamp(const float x) const 
    {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }
};

#endif