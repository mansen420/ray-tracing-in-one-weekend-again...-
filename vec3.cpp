#include "vec3.h"
#include "cmath"
vec3::vec3 (float e1, float e2, float e3){ e[0] = e1, e[1] = e2, e[2] = e3; }
vec3::vec3 (const vec3& v) { *this = v; }
vec3& vec3::operator = (const vec3& v)
{
    e[0]=v.x;
    e[1]=v.y;
    e[2]=v.z;
    return *this;
}

vec3 operator+ (const vec3 &lhs, const vec3 &rhs)
{
    return vec3(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z);
}
vec3 operator- (const vec3& u)
{
    return vec3(-u.x, -u.y, -u.z);
}
vec3 operator- (const vec3 &lhs, const vec3 &rhs)
{
    return lhs+(-rhs);
}
vec3 operator* (const vec3 &lhs, const vec3 &rhs)
{
    return vec3 (lhs.x*rhs.x, lhs.y*rhs.y, lhs.z*rhs.z);
}
vec3 operator/ (const vec3 &lhs, const vec3 &rhs)
{
    return vec3 (lhs.x/rhs.x, lhs.y/rhs.y, lhs.z/rhs.z);
}

vec3 operator+ (const float &t, const vec3 &v)
{
    return vec3(v.x+t, v.y+t, v.z+t);
}
vec3 operator+ (const vec3 &v, const float &t)
{
    return t+v;
}
vec3 operator* (const float &t, const vec3 &v)
{
    return vec3(v.x*t, v.y*t, v.z*t);
}
vec3 operator* (const vec3 &v, const float &t)
{
    return t*v;
}
vec3 operator/ (const vec3 &v, const float &t)
{
    return (1/t)*v;
}

vec3& operator+= (vec3 &lhs, const vec3 &rhs)
{
    return lhs = lhs + rhs;
}
vec3& operator-= (vec3 &lhs, const vec3 &rhs)
{
    return lhs = lhs - rhs;
}
vec3& operator*= (vec3 &lhs, const vec3 &rhs)
{
    return lhs = lhs * rhs;
}
vec3& operator/= (vec3 &lhs, const vec3 &rhs)
{
    return lhs = lhs / rhs;
}

vec3& operator+= (vec3 &v, const float &t)
{
    return v = v + t;
}
vec3& operator-= (vec3 &v, const float &t)
{
    return v = v - t;
}
vec3& operator*= (vec3 &v, const float &t)
{
    return v = v * t;
}
vec3& operator/= (vec3 &v, const float &t)
{
    return v = v / t;
}

std::ostream& operator<< (std::ostream& s, vec3& v)
{
    s << v.x << ' ' << v.y << ' ' << v.z << ' ';
    return s;
}

//vector utils
float dot (const vec3 &u, const vec3 &v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}
vec3 cross(const vec3 &u, const vec3 &v) 
{
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}
float vec3::magnitudeSquared() const
{
    return dot(*this, *this);
}
float vec3::magnitude() const
{
    return sqrt(magnitudeSquared());
}
vec3 normalized(const vec3 &v)
{
    return v/v.magnitude();
}
//color utils
const color mapColor(const color& c) 
{   //maps color values from [0, 1] to [0, 255]       
    color result = color (static_cast<int>(c.r*255.999), static_cast<int>(c.g*255.999), static_cast<int>(c.b*255.999));    
    return result;
}