#ifndef CAMERA
#define CAMERA

#include "ray.h"
#include "global_constants.h"

class camera 
{
public:
    const point eye = lookFrom;

    //camera-relative orthonormal basis
    const vec3 w = normalized(lookFrom - lookAt);
    const vec3 u = cross(vup, w);
    const vec3 v = cross(w, u);

    const vec3 focal_direction = FOCUS_DIST * w;
    const vec3 viewport_up = VIEWPORT_HEIGHT * v;
    const vec3 viewport_right = VIEWPORT_WIDTH * u;

    const point bottom_left_pixel  = eye - focal_direction - (viewport_up / 2) - (viewport_right / 2);

    const vec3 pixel_delta_right = viewport_right / PX_WIDTH;
    const vec3 pixel_delta_up = viewport_up / PX_HEIGHT;

    const point pixel00_loc = bottom_left_pixel + (pixel_delta_right/2) + (pixel_delta_up/2);

    const float defocus_radius = FOCUS_DIST * tan(RADIANS(defocus_angle / 2));
    const vec3 defocus_disk_right = u * defocus_radius;
    const vec3 defocus_disk_up = v * defocus_radius;

    camera(){}
    //returns a ray pointing from the camera center to the center of the specified pixel index
    ray eyeToPixel(const int pixelX, const int pixelY) const
    {
        return ray(eye, pixel00_loc + pixelX * pixel_delta_right + pixelY * pixel_delta_up);
    }
    //returns a ray pointing from the camera center to the point specified by the real valued pixel location
    ray eyeToPixel(const float pixelX, const float pixelY) const
    {
        point origin = defocus_angle <= 0 ? eye : defocus_disk_sample();
        return ray(origin, pixel00_loc + pixelX * pixel_delta_right + pixelY * pixel_delta_up);
    }
    point defocus_disk_sample() const
    {
        vec3 displacement = random_in_unit_disk();
        return eye + (displacement.x * defocus_disk_right) + (displacement.y * defocus_disk_up);
    }
};

#endif