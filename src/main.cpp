#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "../include/geometry.h"
#include "../include/camera.h"
#include "../include/material.h"

void writeImage(color* pixelBuffer);
static std::vector<hittable*> scene;
static int bounceDepth = 0;
static int samplesPerPixel = 65;
color trace (const ray &r)
{
    if (bounceDepth >= 150)
    {
        bounceDepth = 0;
        return color(0, 0, 0);
    }
    record intersectionInfo;
    bool hitObject = false;
    float closestIntersection = INF;
    for (const hittable* const &object : scene)
    {
        if (object->intersect(r, interval(0.001f, closestIntersection), intersectionInfo))
        {
            closestIntersection = intersectionInfo.t;
            hitObject = true;
        }
    }
    if (hitObject)
    {
        ray scatteredRay;
        color attenuation;
        if (intersectionInfo.matPtr->scatter(r, intersectionInfo, attenuation, scatteredRay))
        {
            if (intersectionInfo.matPtr->emissive)
            {
                bounceDepth = 0;
                return attenuation;
            }
            bounceDepth++;
            return attenuation * trace(scatteredRay);
        }
        bounceDepth = 0;
        return color (0, 0, 0);
    }
    bounceDepth = 0;
    //ambience
    float t = normalized(r.direction).y;  //[-viewportW/2, viewportW/2]
    t += VIEWPORT_HEIGHT/2;              // [0, viewportW]
    t /= VIEWPORT_HEIGHT;               //  [0, 1]
    color result = 
    color(0.0f, 0.0f, 0.0f)*t + color(1.f, 1.f, 1.f)*(1-t);
   // return result;
    return color(1.0f*t, 0.0f*t, 0.0f*t); 
}
int main ()
{
    camera cam;
    color* pixelBuffer = new color[PX_HEIGHT*PX_WIDTH]; //put it on the heap to avoid stack overflow
    metal grayMetal (color (0.55, 0.78, 1.0), 0.15f);
    metal redMetal (color (1.0, 0.65, 0.65), 0.4f);
    diffuse redDiffuse (color(1.0, 0.25, 0.25));
    dialectric d(1.5f);
    light l(color(1, 1, 1));
    light lAmbient (color(1.0, 0.45, 0.6));
    scene.push_back(new sphere(point(0, 0.25, -1.2), 0.5f, &grayMetal));
    scene.push_back(new sphere(point(0.5, -20.0, -4.0), 20.f, &redMetal));
    scene.push_back(new sphere(point(0.0, -0.15, -0.75), 0.1, &redDiffuse));
    scene.push_back(new sphere(point(2.2, 1, -1), 1.5, &l));
    scene.push_back(new sphere(point(-20, 0, -4), 10, &lAmbient));
    for (int i = 0; i < PX_HEIGHT; i++)
    {
        for (int j = 0; j < PX_WIDTH; j++)
        {
            std::cout << "\rLines remaining : " << PX_HEIGHT-i << ' ';
            //sample multiple rays through the same pixel square, then average the results
            color c(0, 0, 0);
            for (int k = 0; k < samplesPerPixel; k++)
            {
                ray r = cam.eyeToPixel( float(j + random_f() - 0.5), float(i + random_f() - 0.5));
                c += trace(r);
            }
            //process color
            c /= samplesPerPixel;
            c.r = sqrt(c.r), c.g = sqrt(c.g), c.b=sqrt(c.b);
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