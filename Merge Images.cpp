
Image ResizeTo(Image& src, int newWidth, int newHeight) {
    Image resizedImage(newWidth, newHeight);

    float scaleX = (float)src.width / newWidth;
    float scaleY = (float)src.height / newHeight;

    for (int i = 0; i < newWidth; ++i) {
        for (int j = 0; j < newHeight; ++j) {
            int origX = (int)(i * scaleX);
            int origY = (int)(j * scaleY);

            if (origX >= src.width) origX = src.width - 1;
            if (origY >= src.height) origY = src.height - 1;

            for (int k = 0; k < 3; ++k) {
                resizedImage(i, j, k) = src(origX, origY, k);
            }
        }
    }
    return resizedImage;
}


void MergeImages(Image& img) {
    string filename2;
    cout << "Enter second image name: ";
    cin >> filename2;

    Image img2(filename2);

    int sizeChoice = 0;
    if (img.width != img2.width || img.height != img2.height) {
        cout << "Images have different sizes:\n";
        cout << "Image1: " << img.width << " x " << img.height << "\n";
        cout << "Image2: " << img2.width << " x " << img2.height << "\n";

        cout << "1) Resize Image2 to Image1 size\n";
        cout << "2) Resize Image1 to Image2 size\n";
        cout << "3) Merge common area only\n";
        cout << "Enter choice: ";
        cin >> sizeChoice;

        if (sizeChoice == 1) {
            img2 = ResizeTo(img2, img.width, img.height);
        }
        else if (sizeChoice == 2) {
            img = ResizeTo(img, img2.width, img2.height);
        }
        else if (sizeChoice != 3) {
            cout << "Invalid choice! Default: resize Image2 to Image1 size.\n";
            img2 = ResizeTo(img2, img.width, img.height);
            sizeChoice = 1;
        }
    }

    int mode;
    cout << "Merge mode -> 1 for Average, 2 for Weighted(alpha): ";
    cin >> mode;

    float alpha = 0.5f;
    if (mode == 2) {
        cout << "Enter alpha for Image1 (0.0 to 1.0): ";
        cin >> alpha;
        if (alpha < 0.0f) alpha = 0.0f;
        if (alpha > 1.0f) alpha = 1.0f;
    }

    int w = img.width, h = img.height;
    if (sizeChoice == 3) {
        w = (img.width < img2.width) ? img.width : img2.width;
        h = (img.height < img2.height) ? img.height : img2.height;
    }

    Image merged(w, h);

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            for (int k = 0; k < 3; ++k) {
                int p1 = img(i, j, k);
                int p2 = img2(i, j, k);

                int out;
                if (mode == 2) out = (int)(alpha * p1 + (1.0f - alpha) * p2);
                else out = (p1 + p2) / 2;

                if (out < 0) out = 0;
                if (out > 255) out = 255;

                merged(i, j, k) = out;
            }
        }
    }

    img = merged;
}