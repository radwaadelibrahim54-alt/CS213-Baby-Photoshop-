#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include "Image_Class.h"
using namespace std;
void purpleimage(Image& img)
{
	double num;
	cout << "Enter purple number : " << endl;
	cin >> num;
	for (int i = 0; i < img.width; i++)
	{
		for(int j = 0; j < img.height ; j++)
		{

			for (int k = 0; k < 3; k++)
			{
				if (k == 0) {
					int val =img(i, j, k) * num;
					if (val > 255)
					{
						val = 255;
					}
				}
				else if (k == 1) {
					img(i, j, k) = 0.2;
				}
				else if (k == 2) {
					int val = img(i, j, k) * num;
					if (val > 255)
					{
						val = 255;
					}
				}
			}
		}


	}
}
int main()
{
	string filename;
	cout << "Enter image name : ";
	cin >> filename;
	Image img(filename);
	cout << "15.purpleimage" << endl;
	cout << "Enter choice : ";
	int choice;
	cin >> choice;
	if (choice == 15)
	{
		purpleimage(img);
	}
	cout << "Enter new image name : ";
	cin >> filename;
	img.saveImage(filename);
	return 0;
}
