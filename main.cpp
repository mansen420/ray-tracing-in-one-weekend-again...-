#include <iostream>
#include <fstream>
#include "vec3.h"
#include "global_constants.h"

void writeImage(color* pixelBuffer);
int main ()
{
    color pixelBuffer[PX_WIDTH*PX_HEIGHT];
    for (int i = 0; i < PX_HEIGHT; i++)
    {
        std::cout << "\rLines remaining : " << PX_HEIGHT-i << ' ';
        for (int j = 0; j < PX_WIDTH; j++)
        {
            pixelBuffer[j + i*PX_HEIGHT] = mapColor ( color((double(i)/(PX_HEIGHT-1)), 0.25, ((double)(j)/(PX_WIDTH-1))) );
        }
    }
    std::cout << "\nDone rendering!" << std::endl;
    writeImage(pixelBuffer);
    return 0;
}
void writeImage(color* pixelBuffer)
{
    std::ofstream image("image.ppm");
    image << "P3\n" << PX_WIDTH << " " << PX_HEIGHT << "\n255\n";
    for (int i = 0; i < PX_HEIGHT; i++)
    {
        for (int j = 0; j < PX_WIDTH; j++)
        {
            image << pixelBuffer[j + PX_HEIGHT*i];
        }
        image <<"\n";
    }
    image.close();
}
