// filter 9 : merge image
void mergeImages(Image img1, Image img2) {
    int finalWidth, finalHeight;
    int choice = 0;

    if (img1.width == img2.width && img1.height == img2.height) {
        finalWidth = img1.width;
        finalHeight = img1.height;
    }
    else {
        cout << "1. Merge common area (smaller dimensions)\n";
        cout << "2. Resize images to maximum dimensions\n";
        cout << "Enter choice (1 or 2): ";
        cin >> choice;

        if (choice == 1)
        {
            if (img1.width < img2.width)
            {
                finalWidth = img1.width;
            }
            else
            {
                finalWidth = img2.width;
            }
            if (img1.height < img2.height)
            {
                finalHeight = img1.height;
            }
            else
            {
                finalHeight = img2.height;
            }
        }

        else if (choice == 2) {
            if (img1.width > img2.width)
            {
                finalWidth = img1.width;
            }
            else
            {
                finalWidth = img2.width;
            }
            if (img1.height > img2.height)
            {
                finalHeight = img1.height;
            }
            else
            {
                finalHeight = img2.height;
            }
            Image resized1(finalWidth, finalHeight);
            for (int i = 0; i < finalWidth; i++) {
                for (int j = 0; j < finalHeight; j++) {
                    int origX = i * img1.width / finalWidth;
                    int origY = j * img1.height / finalHeight;
                    for (int c = 0; c < 3; c++) {
                        resized1(i, j, c) = img1(origX, origY, c);
                    }
                }
            }
            img1 = resized1;

            Image resized2(finalWidth, finalHeight);
            for (int i = 0; i < finalWidth; i++) {
                for (int j = 0; j < finalHeight; j++) {
                    int origX = i * img2.width / finalWidth;
                    int origY = j * img2.height / finalHeight;
                    for (int c = 0; c < 3; c++) {
                        resized2(i, j, c) = img2(origX, origY, c);
                    }
                }
            }
            img2 = resized2;
        }
    }

    Image mergedImg(finalWidth, finalHeight);

    for (int i = 0; i < finalWidth; i++) {
        for (int j = 0; j < finalHeight; j++) {
            for (int c = 0; c < 3; c++) {
                mergedImg(i, j, c) = (img1(i, j, c) + img2(i, j, c)) / 2;
            }
        }
    }

    mergedImg.saveImage("merged_output.jpg");
}
