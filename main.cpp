#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<string>
#include"Image_Class.h"
using namespace std;

void filter4() {
    string filename;
    cout << "please Enter image name:" << endl;
    cin >> filename;
    Image image(filename);
    int width = image.width;
    int height = image.height;
    int frameSize;
    cout << "Enter frameSize:" << endl;
    cin >> frameSize;
    while (frameSize <= 0 || frameSize * 2 >= width || frameSize * 2 >= height)
    {
        cout << "invalid frame size please enter anther frameSize" << endl;
        cin >> frameSize;
    }
    cout << "choose frame type -> 1 for simple , 2 for fancy" << endl;
    int type;
    cin >> type;
    int R, G, B;
    cout << "Enter RGB colour values (0-255) " << endl;
    cout << "Red : ";
    cin >> R;
    cout << "Green : ";
    cin >> G;
    cout << "Blue: ";
    cin >> B;
    if (type == 1) {
        for (int i = 0; i < image.height; i++) {
            for (int j = 0; j < image.width; j++) {
                if (i < frameSize || i >= height - frameSize || j < frameSize || j >= width - frameSize)
                {
                    image(j, i, 0) = R;
                    image(j, i, 1) = G;
                    image(j, i, 2) = B;
                }
            }
        }
    }
    else if (type == 2)
    {
        int outerLimit = frameSize;
        int whiteLimit = outerLimit + 5;
        int innerLimit = whiteLimit + 10;
        for (int i = 0; i < image.height; i++)
        {
            for (int j = 0; j < image.width; j++)
            {
                if ((i < outerLimit || i >= height - outerLimit || j < outerLimit || j >= width - outerLimit) ||
                    (i >= whiteLimit && i < innerLimit) || (i >= height - innerLimit && i < height - whiteLimit) ||
                    (j >= whiteLimit && j < innerLimit) || (j >= width - innerLimit && j < width - whiteLimit))
                {
                    image(j, i, 0) = R;
                    image(j, i, 1) = G;
                    image(j, i, 2) = B;
                }
                else if (i < whiteLimit || i >= height - whiteLimit || j < whiteLimit || j >= width - whiteLimit)
                {
                    image(j, i, 0) = 255;
                    image(j, i, 1) = 255;
                    image(j, i, 2) = 255;
                }
            }
        }
    }
    image.saveImage("framed_image.jpg");
    system("framed_image.jpg");
}
void filter8()
{
    string filename;
    cout << "please Enter image name:" << endl;
    cin >> filename;
    Image image(filename);
    int type;
    cout << "1 for dimensions OR 2 for ratio" << endl;
    cin >> type;
    int newWidth, newHeight;
    float r;
    if (type == 1)
    {
        cout << "Enter newWidth: ";
        cin >> newWidth;
        cout << "Enter newHeight: ";
        cin >> newHeight;
    }
    else if (type == 2)
    {
        cout << "Enter r: ";
        cin >> r;
        newWidth = r * image.width;
        newHeight = r * image.height;
    }
    Image resizedImage(newWidth, newHeight);
    float scaleX = (float)image.width / newWidth;
    float scaleY = (float)image.height / newHeight;

    for (int i = 0; i < resizedImage.height; i++)
    {
        for (int j = 0; j < resizedImage.width; j++)
        {
            int origX = j * scaleX;
            int origY = i * scaleY;
            for (int k = 0; k < 3; k++)
            {
                resizedImage(j, i, k) = image(origX, origY, k);
            }
        }
    }
    resizedImage.saveImage("resized_image.jpg");
    system("resized_image.jpg");
}
int main()
{
    filter4();
    filter8();
    return 0;
}

