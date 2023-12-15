#ifndef CAMERA
#define CAMERA

#include "ray.h"
#include "global_constants.h"

class camera 
{
public:
    const point eye = point(0.0f, 0.0f, 0.f);

    const vec3 focal_length = vec3(0.f, 0.f, 1.f);
    const vec3 viewport_up = vec3(0.f, VIEWPORT_HEIGHT, 0.f);
    const vec3 viewport_right = vec3(VIEWPORT_WIDTH, 0.f, 0.f);
    const point bottom_left_pixel  = eye - focal_length - (viewport_up / 2) - (viewport_right / 2);

    const vec3 pixel_delta_right = viewport_right / PX_WIDTH;
    const vec3 pixel_delta_up = viewport_up / PX_HEIGHT;
    const point pixel00_loc = bottom_left_pixel + (pixel_delta_right/2) + (pixel_delta_up/2);

    camera(){}
    //returns a ray pointing from the camera center to the center of the specified pixel index
    ray eyeToPixel(const int pixelX, const int pixelY) const
    {
        return ray(eye, pixel00_loc + pixelX * pixel_delta_right + pixelY * pixel_delta_up);
    }
    //returns a ray pointing from the camera center to the point specified by the real valued pixel location
    ray eyeToPixel(const float pixelX, const float pixelY) const
    {
        return ray(eye, pixel00_loc + pixelX * pixel_delta_right + pixelY * pixel_delta_up);
    }
};

#endif