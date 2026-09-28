#include "Image_Class.h"
#include <iostream>
using namespace std;

void Grayscale(Image& mario)
{
    for (int i = 0; i < mario.width; i++)
    {
        for (int j = 0; j < mario.height; j++)
        {
            int gray = 0.299 * mario(i, j, 0)
                     + 0.587 * mario(i, j, 1)
                     + 0.114 * mario(i, j, 2);

            mario(i, j, 0) = gray;
            mario(i, j, 1) = gray;
            mario(i, j, 2) = gray;
        }
    }
}


int main()
{
    Mat image = imread("mario.jpg");

    if (image.empty())
    {
        return -1;
    }

    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);

    imwrite("gray_image.jpg", gray);

    return 0;
}
