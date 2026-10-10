#pragma once
#define _CRT_SECURE_NO_WARNINGS

#ifndef _IMAGE_CLASS_H
#define _IMAGE_CLASS_H

#define ll long long
#define PNG_TYPE 1
#define BMP_TYPE 2
#define TGA_TYPE 3
#define JPG_TYPE 4
#define UNSUPPORTED_TYPE -1

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define pixel unsigned int

#include <iostream>
#include <exception>

class Image {
private:
    bool isValidFilename(const std::string& filename) {
        const char* extension = strrchr(filename.c_str(), '.');
        if (extension == nullptr) {
            std::cerr << "Invalid filename: " << filename << std::endl;
            return false;
        }
        return true;
    }

    short getExtensionType(const char* extension) {
        if (strcmp(extension, ".png") == 0) {
            return PNG_TYPE;
        }
        if (strcmp(extension, ".bmp") == 0) {
            return BMP_TYPE;
        }
        if (strcmp(extension, ".tga") == 0) {
            return TGA_TYPE;
        }
        if (strcmp(extension, ".jpg") == 0 || strcmp(extension, ".jpeg") == 0) {
            return JPG_TYPE;
        }

        std::cerr << "Unsupported image format: " << extension << std::endl;
        return UNSUPPORTED_TYPE;
    }

private:
    std::string filename;

public:
    int width = 0;
    int height = 0;
    int channels = 3;
    unsigned char* imageData = nullptr;

    Image() = default;

    Image(std::string filename) : filename((filename)) {
        loadNewImage(this->filename);
    }

    Image(int mWidth, int mHeight) {
        this->width = mWidth;
        this->height = mHeight;
        this->imageData = (unsigned char*)malloc(mWidth * mHeight * this->channels);
    }

    Image(const Image& other) {
        *this = other;
    }

    Image& operator=(const Image& image) {
        if (this == &image) {
            return *this;
        }

        stbi_image_free(this->imageData);
        this->imageData = nullptr;

        this->width = image.width;
        this->height = image.height;
        this->channels = image.channels;
        imageData = static_cast<unsigned char*>(malloc(width * height * channels));

        for (int i = 0; i < image.width * image.height * this->channels; i++) {
            this->imageData[i] = image.imageData[i];
        }

        return *this;
    }

    ~Image() {
        if (imageData != nullptr) {
            stbi_image_free(imageData);
        }
        this->width = 0;
        this->height = 0;
        this->imageData = nullptr;
    }

    bool loadNewImage(const std::string& filename) {
        if (!isValidFilename(filename)) {
            std::cerr << "Couldn't Load Image" << '\n';
            throw std::invalid_argument("The file extension does not exist");
        }

        const char* extension = strrchr(filename.c_str(), '.');
        short extensionType = getExtensionType(extension);
        if (extensionType == UNSUPPORTED_TYPE) {
            std::cerr << "Unsupported File Format" << '\n';
            throw std::invalid_argument("File Extension is not supported, Only .JPG, JPEG, .BMP, .PNG, .TGA are supported");
        }
        if (imageData != nullptr) {
            stbi_image_free(imageData);
        }

        imageData = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb);
        this->channels = 3;

        if (imageData == nullptr) {
            std::cerr << "File Doesn't Exist" << '\n';
            throw std::invalid_argument("Invalid filename, File Does not Exist");
        }

        return true;
    }

    bool saveImage(const std::string& outputFilename) {
        if (!isValidFilename(outputFilename)) {
            std::cerr << "Not Supported Format" << '\n';
            throw std::invalid_argument("The file extension does not exist");
        }

        const char* extension = strrchr(outputFilename.c_str(), '.');
        short extensionType = getExtensionType(extension);
        if (extensionType == UNSUPPORTED_TYPE) {
            std::cerr << "File Extension is not supported, Only .JPG, JPEG, .BMP, .PNG, .TGA are supported" << '\n';
            throw std::invalid_argument("File Extension is not supported, Only .JPG, JPEG, .BMP, .PNG, .TGA are supported");
        }

        if (extensionType == PNG_TYPE) {
            stbi_write_png(outputFilename.c_str(), width, height, STBI_rgb, imageData, width * 3);
        }
        else if (extensionType == BMP_TYPE) {
            stbi_write_bmp(outputFilename.c_str(), width, height, STBI_rgb, imageData);
        }
        else if (extensionType == TGA_TYPE) {
            stbi_write_tga(outputFilename.c_str(), width, height, STBI_rgb, imageData);
        }
        else if (extensionType == JPG_TYPE) {
            stbi_write_jpg(outputFilename.c_str(), width, height, STBI_rgb, imageData, 90);
        }

        return true;
    }

    unsigned char& getPixel(int x, int y, int c) {
        if (x > width || x < 0) {
            std::cerr << "Out of width bounds" << '\n';
            throw std::out_of_range("Out of bounds, Cannot exceed width value");
        }
        if (y > height || y < 0) {
            std::cerr << "Out of height bounds" << '\n';
            throw std::out_of_range("Out of bounds, Cannot exceed height value");
        }
        if (c < 0 || c > 2) {
            std::cerr << "Out of channels bounds" << '\n';
            throw std::out_of_range("Out of bounds, You only have 3 channels in RGB");
        }

        return imageData[(y * width + x) * channels + c];
    }

    const unsigned char& getPixel(int x, int y, int c) const {
        if (x > width || x < 0) {
            std::cerr << "Out of width bounds" << '\n';
            throw std::out_of_range("Out of bounds, Cannot exceed width value");
        }
        if (y > height || y < 0) {
            std::cerr << "Out of height bounds" << '\n';
            throw std::out_of_range("Out of bounds, Cannot exceed height value");
        }
        if (c < 0 || c > 2) {
            std::cerr << "Out of channels bounds" << '\n';
            throw std::out_of_range("Out of bounds, You only have 3 channels in RGB");
        }

        return imageData[(y * width + x) * channels + c];
    }

    void setPixel(int x, int y, int c, unsigned char value) {
        if (x > width || x < 0) {
            std::cerr << "Out of width bounds" << '\n';
            throw std::out_of_range("Out of bounds, Cannot exceed width value");
        }
        if (y > height || y < 0) {
            std::cerr << "Out of height bounds" << '\n';
            throw std::out_of_range("Out of bounds, Cannot exceed height value");
        }
        if (c < 0 || c > 2) {
            std::cerr << "Out of channels bounds" << '\n';
            throw std::out_of_range("Out of bounds, You only have 3 channels in RGB");
        }

        imageData[(y * width + x) * channels + c] = value;
    }

    const unsigned char& operator()(int row, int col, int channel) const {
        return getPixel(row, col, channel);
    }

    unsigned char& operator()(int row, int col, int channel) {
        return getPixel(row, col, channel);
    }
};

#endif