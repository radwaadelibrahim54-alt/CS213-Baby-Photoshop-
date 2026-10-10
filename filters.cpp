
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<string>
#include "Image_Class.h"
using namespace std;

void Blur(Image& img)
{
    int level;
    cout << "Please Enter Level of Blur:";
    cin >> level;
    if (level > 10)
    {
        level = 10;
    }
    else if (level < 1)
    {
        level = 1;
    }
    Image blurredimg(img.width, img.height);
    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            int sumR = 0, sumG = 0, sumB = 0, count = 0;
            for (int x = -level; x <= level; x++)
            {
                for (int y = -level; y <= level; y++)
                {
                    int ni = i + x;
                    int nj = j + y;

                    if (ni >= 0 && ni < img.width && nj >= 0 && nj < img.height)
                    {
                        sumR += img(ni, nj, 0);
                        sumG += img(ni, nj, 1);
                        sumB += img(ni, nj, 2);
                        count++;
                    }
                }
            }
            blurredimg(i, j, 0) = sumR / count;
            blurredimg(i, j, 1) = sumG / count;
            blurredimg(i, j, 2) = sumB / count;
        }
    }
    img = blurredimg;
}
void infrared(Image& img)
{
    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            int orig_red = img(i, j, 0);
            img(i, j, 0) = 255;
            img(i, j, 1) = 255 - orig_red;
            img(i, j, 2) = 255 - orig_red;
        }
    }
}
int main()
{
    cout << "choose a filter to test\n";
    cout << "12 -> Blur\n";
    cout << "16 -> infrared\n";
    cout << "Enter Choice:";

    int choice;
    cin >> choice;
    string filename;
    cout << "Enter image name:";
    cin >> filename;

    Image img(filename);
    if (choice == 12)
    {
        Blur(img);
    }
    else if (choice == 16)
    {
        infrared(img);
    }
    string outputName;
    cout << "Enter outputName to save image:";
    cin >> outputName;

    img.saveImage(outputName);
    return 0;
}