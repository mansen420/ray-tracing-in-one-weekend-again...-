#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "../include/geometry.h"
#include "../include/camera.h"

void writeImage(color* pixelBuffer);
static std::vector<hittable*> scene;
static int bounceDepth = 0;
static int samplesPerPixel = 25;
color trace (const ray &r)
{
    record intersectionInfo;
    bool hitObject = false;
    float closestIntersection = INF;
    for (const hittable* const &object : scene)
    {
        if (object->intersect(r, interval(0, closestIntersection), intersectionInfo))
        {
            closestIntersection = intersectionInfo.t;
            hitObject = true;
        }
    }
    if (hitObject)
        return 0.5 * intersectionInfo.normal + 0.5;
    bounceDepth = 0;    //reset bounce depth

    //background
    float t = normalized(r.direction).y;  //[-viewportW/2, viewportW/2]
    t += VIEWPORT_HEIGHT/2;              // [0, viewportW]
    t /= VIEWPORT_HEIGHT;               //  [0, 1]
    color result = 
    color(0.5f, 0.5f, 1.0f)*t + color(1.f, 1.f, 1.f)*(1-t);
    return color(0.25f*t, 0.5f*t, t);
}
int main ()
{
    camera cam;
    color* pixelBuffer = new color[PX_HEIGHT*PX_WIDTH]; //put it on the heap to avoid stack overflow
    scene.push_back(new sphere(point(0, 0.25, -1), 0.5f));
    scene.push_back(new sphere(point(0.5, -20.0, -4.0), 20.f));
    for (int i = 0; i < PX_HEIGHT; i++)
    {
        std::cout << "\rLines remaining : " << PX_HEIGHT-i << ' ';
        for (int j = 0; j < PX_WIDTH; j++)
        {
            //sample multiple rays through the same pixel square, then average the results
            color c(0, 0, 0);
            for (int k = 0; k < samplesPerPixel; k++)
            {
                ray r = cam.eyeToPixel( float(j + random_f() - 0.5), float(i + random_f() - 0.5));
                c += trace(r);
            }
            c /= samplesPerPixel;
            pixelBuffer[j + i * PX_WIDTH] = mapColor(c);
        }
    }
    std::cout << "\nDone rendering!" << std::endl;
    writeImage(pixelBuffer);
    //housekeeping...
    delete[] pixelBuffer;
    for (hittable* const &x : scene)
        delete x;
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