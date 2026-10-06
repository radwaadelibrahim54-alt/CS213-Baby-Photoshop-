#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
#include "Image_Class.h"
using namespace std;
void cropimage(Image & img)
{ 
    int x, y, w, h;
    cout << "Enter (x , y ) and (width , height)" << endl;
	cin >> x >> y >> w >> h;

    Image cropped(w, h);
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                cropped(i, j, k) = img(x + i, y + j, k);
            }
        }
    }

    img = cropped;



}
int main()
{
    string filename;
    cout << "Enter image name : ";
    cin >> filename;
    Image img(filename);
    cout << "11.cropimage" << endl;
    cout << "Enter choice : ";
    int choice;
    cin >> choice;

    if (choice == 11)
    {
        cropimage(img);
    }
    cout << "Enter new image name : ";
        cin >> filename;
        img.saveImage(filename);
        return 0;
}