#define _CRT_SECURE_NO_WARNINGS
#include "Image_Class.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void filter10()
{
    string filename;
    cout << "Please enter image name (e.g., test.jpg): " << endl;
    cin >> filename;
    Image image(filename);

    Image edgesImage(image.width, image.height);

    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {

            int avg = (image(x, y, 0) + image(x, y, 1) + image(x, y, 2)) / 3;
            int bw_value;

            if (avg > 127) {
                bw_value = 255;
            }
            else {
                bw_value = 0;
            }

            image(x, y, 0) = bw_value;
            image(x, y, 1) = bw_value;
            image(x, y, 2) = bw_value;
        }
    }

    for (int y = 0; y < image.height - 1; y++) {
        for (int x = 0; x < image.width - 1; x++) {

            int currentPixel = image(x, y, 0);
            int rightPixel = image(x + 1, y, 0);
            int bottomPixel = image(x, y + 1, 0);

            if (currentPixel != rightPixel || currentPixel != bottomPixel) {
                edgesImage(x, y, 0) = 0;
                edgesImage(x, y, 1) = 0;
                edgesImage(x, y, 2) = 0;
            }
            else {
                edgesImage(x, y, 0) = 255;
                edgesImage(x, y, 1) = 255;
                edgesImage(x, y, 2) = 255;
            }
        }
    }

    edgesImage.saveImage("edges_image.jpg");
    system("edges_image.jpg");
}

void filter14()
{
    string filename;
    cout << "Please enter image name (e.g., test.jpg): " << endl;
    cin >> filename;
    Image image(filename);

    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {

            if (y % 3 == 0) {
                image(x, y, 0) = image(x, y, 0) * 0.5;
                image(x, y, 1) = image(x, y, 1) * 0.5;
                image(x, y, 2) = image(x, y, 2) * 0.5;
            }
            else {
                image(x, y, 0) = min(255, (int)(image(x, y, 0) * 0.9));
                image(x, y, 1) = min(255, (int)(image(x, y, 1) * 1.1));
                image(x, y, 2) = min(255, (int)(image(x, y, 2) * 1.2));
            }
        }
    }

    image.saveImage("old_tv_image.jpg");
    system("old_tv_image.jpg");
}

int main()
{
    int choice;
    cout << "Welcome! Choose a filter to test:" << endl;
    cout << "1. Detect Image Edges" << endl;
    cout << "2. Old TV Effect (Wano)" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        filter10();
    }
    else if (choice == 2) {
        filter14();
    }
    else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}