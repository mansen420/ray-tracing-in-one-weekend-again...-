#ifndef GLOBAL_CONST
#define GLOBAL_CONST
#include <cmath>
//image properties
constexpr float ASPECT_RATIO = 16.0f/9.0f;
constexpr int PX_HEIGHT = 250;
constexpr float IDEAL_WIDTH = PX_HEIGHT * ASPECT_RATIO;
constexpr int PX_WIDTH = IDEAL_WIDTH < 1 ? 1 : static_cast<int>(IDEAL_WIDTH);

//numeric utilities
constexpr float PI = 3.1415926535897932385;
inline constexpr float RADIANS (float degrees) { return degrees * PI / 180.0;}

//virtual viewport properties
constexpr float V_FOV_DEG = 60;     //arbitrary
constexpr float V_FOV_RAD = RADIANS(V_FOV_DEG);

const point lookFrom = point(0, 0, 0);
const point lookAt = vec3(0, 0, -1);

const float FOCUS_DIST = 0.65; 
const float defocus_angle = 0;

    //honorary constexprs...
const float VIEWPORT_HEIGHT = 2 * tan(V_FOV_RAD/2.0) * FOCUS_DIST;
const float VIEWPORT_WIDTH = VIEWPORT_HEIGHT * (static_cast<float>(PX_WIDTH)/PX_HEIGHT);

const vec3 vup = normalized(vec3(0.0f, 1.0f, 0.f));

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