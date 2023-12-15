#ifndef GLOBAL_CONST
#define GLOBAL_CONST

//image properties
constexpr float ASPECT_RATIO = 16.0f/9.0f;
constexpr int PX_HEIGHT = 250;
constexpr float IDEAL_WIDTH = PX_HEIGHT * ASPECT_RATIO;
constexpr int PX_WIDTH = IDEAL_WIDTH < 1 ? 1 : static_cast<int>(IDEAL_WIDTH);

//virtual viewport properties
constexpr float VIEWPORT_HEIGHT = 2.0f;             //arbitrary choice
constexpr float VIEWPORT_WIDTH = VIEWPORT_HEIGHT * (static_cast<float>(PX_WIDTH)/PX_HEIGHT);

//numeric utilities
constexpr float PI = 3.1415926535897932385;
inline float RADIANS (float degrees) { return degrees * PI / 180.0;}
// Returns a random real in [0,1).
inline float random_f() 
{
    return rand() / (RAND_MAX + 1.0);
}
inline float random_f(float min, float max) 
{
    return min + (max-min)*random_f();
}

#endif