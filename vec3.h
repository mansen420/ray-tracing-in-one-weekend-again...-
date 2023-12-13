#include <iostream>
struct vec3
{
    float e[3];
    float &x = e[0], &y = e[1], &z = e[2];
    float &r = x, &g = y, &b = z;
    vec3 (float e1 = 0, float e2 = 0, float e3 = 0){e[0] = e1, e[1] = e2, e[2] = e3;}
    vec3 (const vec3& v)
    {
        *this = v;
    }
    vec3& operator = (const vec3& v)
    {
        e[0]=v.x;
        e[1]=v.y;
        e[2]=v.z;
        return *this;
    }
};
typedef vec3 point;
typedef vec3 color;
std::ostream& operator<< (std::ostream& s, vec3& v)
{
    s << v.x << ' ' << v.y << ' ' << v.z << ' ';
    return s;
}
//color utils
const color mapColor(const color& c) 
{   //maps color values from [0, 1] to [0, 255]       
    color result = color (static_cast<int>(c.r*255.999), static_cast<int>(c.g*255.999), static_cast<int>(c.b*255.999));    
    return result;
}
 