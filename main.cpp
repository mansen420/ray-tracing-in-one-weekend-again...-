#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"
#include "global_constants.h"

void writeImage(color* pixelBuffer);
color traceRays (ray r)
{
    float t = r.rayDirection.y; // [-viewport height/2, viewport height/2]
    t += VIEWPORT_HEIGHT/2;     // [0, viewport height]
    return color(0.f, 0.f, t/(VIEWPORT_HEIGHT));
}
int main ()
{
    //camera and viewport properties 
    const point eye = point(0.f, 0.f, 0.f);

    const vec3 focal_length = vec3(0.f, 0.f, -1.0f);
    const vec3 viewport_up = vec3(0.f, VIEWPORT_HEIGHT, 0.f);
    const vec3 viewport_right = vec3(VIEWPORT_WIDTH, 0.f, 0.f);
    const point bottom_left_pixel  = eye - focal_length - (viewport_up / 2) - (viewport_right / 2);

    const vec3 pixel_delta_right = viewport_right / PX_WIDTH;
    const vec3 pixel_delta_up = viewport_up / PX_HEIGHT;
    const point pixel00_loc = bottom_left_pixel + (pixel_delta_right/2) + (pixel_delta_up/2);

    color pixelBuffer[PX_WIDTH*PX_HEIGHT];
    for (int i = 0; i < PX_HEIGHT; i++)
    {
        std::cout << "\rLines remaining : " << PX_HEIGHT-i << ' ';
        for (int j = 0; j < PX_WIDTH; j++)
        {
            point currentPixelCenter = pixel00_loc + pixel_delta_right * j + pixel_delta_up * i;
            ray r = ray (eye, eye - currentPixelCenter);
            color c = traceRays(r);
            pixelBuffer[j + i * PX_WIDTH] = mapColor(c);
        }
    }
    std::cout << "\nDone rendering!" << std::endl;
    writeImage(pixelBuffer);
    return 0;
}
void writeImage(color* pixelBuffer)
{   //prints pixelBuffer to image.ppm, where [0, 0] corresponds to the bottom left pixel.
    std::ofstream image("image.ppm");
    image << "P3\n" << PX_WIDTH << " " << PX_HEIGHT << "\n255\n";
    for (int i = 0; i < PX_HEIGHT; i++)
    {
        for (int j = 0; j < PX_WIDTH; j++)
        {
            image << pixelBuffer[j + (PX_WIDTH * (PX_HEIGHT - 1 - i ))];
        }
        image << "\n";
    }
    image.close();
}
