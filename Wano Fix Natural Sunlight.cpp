int clamp255(int v) {
    if (v < 0) return 0;
    if (v > 255) return 255;
    return v;
}

void FixNaturalSunlight(Image& img) {
    int mode;
    cout << "Fix Natural Sunlight -> 1 Auto , 2 Custom: ";
    cin >> mode;

    
    float wbStrength = 0.70f;   
    float warmthR = 1.06f;      
    float warmthB = 0.97f;      
    float sat = 1.12f;         
    float contrast = 1.05f;     
    int brightness = 4;         

    if (mode == 2) {
        cout << "Enter wbStrength (0.0 to 1.0): ";
        cin >> wbStrength;

        cout << "Enter warmthR (e.g. 1.00 to 1.15): ";
        cin >> warmthR;

        cout << "Enter warmthB (e.g. 0.85 to 1.05): ";
        cin >> warmthB;

        cout << "Enter saturation factor sat (e.g. 1.0 to 1.5): ";
        cin >> sat;

        cout << "Enter contrast (e.g. 1.0 to 1.3): ";
        cin >> contrast;

        cout << "Enter brightness (-50 to 50): ";
        cin >> brightness;

        if (wbStrength < 0.0f) wbStrength = 0.0f;
        if (wbStrength > 1.0f) wbStrength = 1.0f;
    }

   
    long long sumR = 0, sumG = 0, sumB = 0;
    long long total = (long long)img.width * img.height;

    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            sumR += img(i, j, 0);
            sumG += img(i, j, 1);
            sumB += img(i, j, 2);
        }
    }

    float avgR = (total ? (float)sumR / total : 0.0f);
    float avgG = (total ? (float)sumG / total : 0.0f);
    float avgB = (total ? (float)sumB / total : 0.0f);

    float gray = (avgR + avgG + avgB) / 3.0f;

    float scaleR = (avgR > 0.0f) ? (gray / avgR) : 1.0f;
    float scaleG = (avgG > 0.0f) ? (gray / avgG) : 1.0f;
    float scaleB = (avgB > 0.0f) ? (gray / avgB) : 1.0f;

    scaleR = 1.0f + wbStrength * (scaleR - 1.0f);
    scaleG = 1.0f + wbStrength * (scaleG - 1.0f);
    scaleB = 1.0f + wbStrength * (scaleB - 1.0f);


    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {

            float r = img(i, j, 0) * scaleR;
            float g = img(i, j, 1) * scaleG;
            float b = img(i, j, 2) * scaleB;

            r *= warmthR;
            b *= warmthB;

          
            float lum = 0.299f * r + 0.587f * g + 0.114f * b;
            r = lum + sat * (r - lum);
            g = lum + sat * (g - lum);
            b = lum + sat * (b - lum);

        
            r = (r - 128.0f) * contrast + 128.0f + brightness;
            g = (g - 128.0f) * contrast + 128.0f + brightness;
            b = (b - 128.0f) * contrast + 128.0f + brightness;

            img(i, j, 0) = clamp255((int)r);
            img(i, j, 1) = clamp255((int)g);
            img(i, j, 2) = clamp255((int)b);
        }
    }
}

int main() {

    cout << "1. Grayscale Image\n";
    cout << "2. Black and White Image\n";
    cout << "3. Invert Image\n";
    cout << "4. Add Frame\n";
    cout << "5. Flip Image\n";
    cout << "6. Rotate Image\n";
    cout << "7. Darken  or ligten Image\n";
    cout << "8. Resize Image\n";
    cout << "9. Merge Images\n";
    cout << "10. Fix Natural Sunlight\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;

    string filename;
    cout << "Enter image name: ";
    cin >> filename;

    Image img(filename);

    if (choice == 1) {
        Grayscale(img);
    }
    else if (choice == 2) {
        BlackandWhite(img);
    }
    else if (choice == 3) {
        invert(img);
    }
    else if (choice == 4) {
        Frame(img);
    }
    else if (choice == 5) {
        Flip(img);
    }
    else if (choice == 6) {
        Rotate(img);
    }
    else if (choice == 7) {
        int subChoice;
        cout << "1 for Darken OR 2 for Lighten: ";
        cin >> subChoice;

        if (subChoice == 1) Darken(img);
        else if (subChoice == 2) lighten(img);
        else cout << "Invalid choice!\n";
    }
    else if (choice == 8) {
        Resize(img);
    }
    else if (choice == 9) {
        MergeImages(img);
    }
    else if (choice == 10) {
        FixNaturalSunlight(img);
    }
    else {
        cout << "Invalid choice!\n";
    }

    string outputName;
    cout << "Enter output image name to save: ";
    cin >> outputName;

    img.saveImage(outputName);

    return 0;
}