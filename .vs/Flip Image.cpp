#include "Image_Class.h"
#include <iostream>
using namespace std;

void FlipImage(Image& mario)
{
    for (int i = 0; i < mario.width / 2; i++)
    {
        for (int j = 0; j < mario.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                swap(mario(i, j, k),
                     mario(mario.width - 1 - i, j, k));
            }
        }
    }
}

int main()
{
    Image mario("mario.jpg");

    FlipImage(mario);

    mario.saveImage("flipped_mario.jpg");

    return 0;
}