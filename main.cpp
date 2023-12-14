#include <iostream>
#include <fstream>
#include <cmath>
#include "vec3.h"
#include "ray.h"
#include "global_constants.h"
#include "geometry.h"

void writeImage(color* pixelBuffer);
static int bounceDepth = 0;
color trace (ray r, sphere s)
{
    record intersectionInfo;
    if (s.intersect(r, 0, 100, intersectionInfo))
    {
        return color(0.5*intersectionInfo.normal+0.5);
    }
    bounceDepth = 0;    //reset bounce depth
    float t = normalized(r.direction).y;  //[-viewportW/2, viewportW/2]
    t += VIEWPORT_HEIGHT/2;              // [0, viewportW]
    t /= VIEWPORT_HEIGHT;               //  [0, 1]
    color result = 
    color(0.5f, 0.5f, 1.0f)*t + color(1.f, 1.f, 1.f)*(1-t);
    return color(0.25f*t, 0.5f*t, t);
}
int main ()
{
    //camera and viewport properties 
    const point eye = point(0.0f, 0.0f, 0.f);

    const vec3 focal_length = vec3(0.f, 0.f, 1.f);
    const vec3 viewport_up = vec3(0.f, VIEWPORT_HEIGHT, 0.f);
    const vec3 viewport_right = vec3(VIEWPORT_WIDTH, 0.f, 0.f);
    const point bottom_left_pixel  = eye - focal_length - (viewport_up / 2) - (viewport_right / 2);

    const vec3 pixel_delta_right = viewport_right / PX_WIDTH;
    const vec3 pixel_delta_up = viewport_up / PX_HEIGHT;
    const point pixel00_loc = bottom_left_pixel + (pixel_delta_right/2) + (pixel_delta_up/2);

    color* pixelBuffer = new color[PX_HEIGHT*PX_WIDTH]; //put it on the heap to avoid stack overflow
    for (int i = 0; i < PX_HEIGHT; i++)
    {
        std::cout << "\rLines remaining : " << PX_HEIGHT-i << ' ';
        for (int j = 0; j < PX_WIDTH; j++)
        {
            point currentPixelCenter = pixel00_loc + pixel_delta_right * j + pixel_delta_up * i;
            ray r = ray (eye, currentPixelCenter - eye);
            color c = trace(r, sphere(point(0, 0, -1), 0.5f));
            pixelBuffer[j + i * PX_WIDTH] = mapColor(c);
        }
    }
    std::cout << "\nDone rendering!" << std::endl;
    writeImage(pixelBuffer);
    delete[] pixelBuffer;
    return 0;
}
void writeImage(color* pixelBuffer)
{   //prints pixelBuffer to image.ppm, vertically inverted, i.e., [0, 0] corresponds to the bottom left pixel.
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
