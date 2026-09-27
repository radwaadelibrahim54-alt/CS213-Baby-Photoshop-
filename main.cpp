#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Image_Class.h"
using namespace std;
 

void invert(Image& luffy)
{

    for (int i = 0;i < luffy.width; i++)
    {
        for (int j = 0; j < luffy.height; j++)
        {
            for (int k = 0; k < 3;k++)
            {
                luffy(i, j, k) = 255 - luffy(i, j, k);



            }
        }
    }

}
void Darken(Image& luffy)


{

    for (int i = 0; i < luffy.width; i++)
    {
        for (int j = 0; j < luffy.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                luffy(i, j, k) *= 0.5;
            }
        }
    }

}

void lighten(Image& luffy)
{
    for (int i = 0; i < luffy.width; i++)
    {

        for (int j = 0; j < luffy.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
			int val	= luffy(i, j, k) * 1.5;
				if (val > 255)
				{
					val = 255;
                    luffy(i, j, k) = val;
					
				}
				
            }
        }
    }
    
  

}
        

int main()
{
    Image image("luffy.jpeg");
    int choice;
    cout << "1.invert Image" << endl;
    cout << "2.Darken Image" << endl;
    cout << "3.lighten Image" << endl;
    cout << "Enter choice:" << endl;
    cin >> choice;

    if (choice == 1)
    {
        invert(image);
        image.saveImage("inverted_luffy.jpeg");
    }
    else if (choice == 2)
    {
        Darken(image);
        image.saveImage("Darkened_luffy.jpeg");
    }
    else if (choice == 3)
    {
        lighten(image);
        image.saveImage("lightined_luffy.jpeg");

    }
    image.saveImage("New_luffy.jpeg");
    return 0;
}







