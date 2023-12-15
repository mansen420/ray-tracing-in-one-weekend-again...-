#ifndef VEC3 
#define VEC3

#include <iostream>
struct vec3
{
    float e[3];
    float &x = e[0], &y = e[1], &z = e[2];
    float &r = x, &g = y, &b = z;
    vec3 (float e1 = 0, float e2 = 0, float e3 = 0);
    vec3 (const vec3& v);
    vec3 &operator = (const vec3& v);
    float magnitudeSquared() const;
    float magnitude() const;
};
typedef vec3 point;
typedef vec3 color;

//operator overloading
vec3 operator+ (const vec3 &lhs, const vec3 &rhs);
vec3 operator- (const vec3& v);
vec3 operator- (const vec3 &lhs, const vec3 &rhs);
vec3 operator* (const vec3 &lhs, const vec3 &rhs);
vec3 operator/ (const vec3 &lhs, const vec3 &rhs);
vec3 operator+ (const float &t, const vec3 &v);
vec3 operator+ (const vec3 &v, const float &t);
vec3 operator* (const float &t, const vec3 &v);
vec3 operator* (const vec3 &v, const float &t);
vec3 operator/ (const vec3 &v, const float &t);
vec3& operator+= (vec3 &lhs, const vec3 &rhs);
vec3& operator-= (vec3 &lhs, const vec3 &rhs);
vec3& operator*= (vec3 &lhs, const vec3 &rhs);
vec3& operator/= (vec3 &lhs, const vec3 &rhs);
vec3& operator+= (vec3 &v, const float &t);
vec3& operator-= (vec3 &v, const float &t);
vec3& operator*= (vec3 &v, const float &t);
vec3& operator/= (vec3 &v, const float &t);
std::ostream& operator<< (std::ostream& s, vec3& v);

//vector utils 
float dot (const vec3 &u, const vec3 &v);
vec3 cross(const vec3 &u, const vec3 &v);
vec3 normalized(const vec3 &v);
//returns a vec3 with random elements in [0, 1)
vec3 random_vec3();
vec3 random_vec3(const float min, const float max);
vec3 random_inside_unit_sphere();
vec3 random_on_unit_sphere();
//color utils
const color mapColor(const color& c);

#endif