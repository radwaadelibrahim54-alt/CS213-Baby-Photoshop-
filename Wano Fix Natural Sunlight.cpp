//filter 13 : Wano image
void Wano(Image& img, int userVal) {
    for (int i = 0; i < img.width ; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < 3; k++) {
                int newValue = img(i, j, k) + userVal;
                if (newValue > 255) {
                    img(i, j, k) = 255;
                }
                else if (newValue < 0) {
                    img(i, j, k) = 0;
                }
                else {
                    img(i, j, k) = newValue;
                }
            }
        }
    }
}
