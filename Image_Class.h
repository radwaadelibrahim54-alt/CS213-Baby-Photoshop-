void filter2()
{
    string filename;
    cout << "please Enter image name:" << endl;
    cin >> filename;
    Image image(filename);

    for (int i = 0; i < image.height; i++)
    {
        for (int j = 0; j < image.width; j++)
        {
            int r = image(j, i, 0);
            int g = image(j, i, 1);
            int b = image(j, i, 2);
            int avg = (r + g + b) / 3;

            if (avg > 127)
            {
                image(j, i, 0) = 255;
                image(j, i, 1) = 255;
                image(j, i, 2) = 255;
            }
            else
            {
                image(j, i, 0) = 0;
                image(j, i, 1) = 0;
                image(j, i, 2) = 0;
            }
        }
    }
    image.saveImage("bw_image.jpg");
    system("bw_image.jpg");
}

void filter6()
{
    string filename;
    cout << "please Enter image name:" << endl;
    cin >> filename;
    Image image(filename);

    int degree;
    cout << "Enter rotation degree (90, 180, or 270): " << endl;
    cin >> degree;

    if (degree == 90 || degree == 270)
    {
        Image rotatedImage(image.height, image.width);
        for (int i = 0; i < image.height; i++)
        {
            for (int j = 0; j < image.width; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    if (degree == 90)
                    {
                        rotatedImage(image.height - 1 - i, j, k) = image(j, i, k);
                    }
                    else if (degree == 270)
                    {
                        rotatedImage(i, image.width - 1 - j, k) = image(j, i, k);
                    }
                }
            }
        }
        rotatedImage.saveImage("rotated_image.jpg");
        system("rotated_image.jpg");
    }
    else if (degree == 180)
    {
        Image rotatedImage(image.width, image.height);
        for (int i = 0; i < image.height; i++)
        {
            for (int j = 0; j < image.width; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    rotatedImage(image.width - 1 - j, image.height - 1 - i, k) = image(j, i, k);
                }
            }
        }
        rotatedImage.saveImage("rotated_image.jpg");
        system("rotated_image.jpg");
    }
    else
    {
        cout << "invalid degree" << endl;
    }
}