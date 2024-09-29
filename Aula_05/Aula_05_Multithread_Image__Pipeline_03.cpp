/*
several image filters and then process them in a pipeline:

Filters:
 1. Grayscale: Converts the image to grayscale.
 2. Invert: Inverts the colors of the image.
 3. Brightness Adjust: Adjusts the brightness of the image.
 4. Contrast Adjust: Adjusts the contrast of the image.
 5. Thresholding: Applies a binary threshold to the image.
 6. Blur: Applies a basic blur effect.
 7. Sharpen: Applies a sharpening effect.
 8. Edge Detection: Detects edges in the image.
 9. Sepia Tone: Applies a sepia tone effect.
 10 .Saturation Adjust: Adjusts the color saturation of the image

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <functional>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./stb_image/stb_image.h"
#include "./stb_image/stb_image_write.h"

struct Pixel {
    unsigned char r, g, b;
};

// Filter function type for flexibility in the pipeline
typedef std::function<void(std::vector<std::vector<Pixel>>&)> FilterFunction;

// Grayscale Filter
void grayscale_filter(std::vector<std::vector<Pixel>>& image) {
    for (auto& row : image) {
        for (auto& pixel : row) {
            unsigned char gray = (pixel.r + pixel.g + pixel.b) / 3;
            pixel.r = gray;
            pixel.g = gray;
            pixel.b = gray;
        }
    }
}

// Invert Filter
void invert_filter(std::vector<std::vector<Pixel>>& image) {
    for (auto& row : image) {
        for (auto& pixel : row) {
            pixel.r = 255 - pixel.r;
            pixel.g = 255 - pixel.g;
            pixel.b = 255 - pixel.b;
        }
    }
}

// Brightness Adjust Filter (scales brightness by a factor)
void brightness_filter(std::vector<std::vector<Pixel>>& image, int factor) {
    for (auto& row : image) {
        for (auto& pixel : row) {
            pixel.r = std::min(255, pixel.r + factor);
            pixel.g = std::min(255, pixel.g + factor);
            pixel.b = std::min(255, pixel.b + factor);
        }
    }
}

// Contrast Adjust Filter (simple contrast stretch)
void contrast_filter(std::vector<std::vector<Pixel>>& image, float factor) {
    for (auto& row : image) {
        for (auto& pixel : row) {
            pixel.r = std::clamp(int(((pixel.r - 128) * factor) + 128), 0, 255);
            pixel.g = std::clamp(int(((pixel.g - 128) * factor) + 128), 0, 255);
            pixel.b = std::clamp(int(((pixel.b - 128) * factor) + 128), 0, 255);
        }
    }
}

// Threshold Filter
void threshold_filter(std::vector<std::vector<Pixel>>& image, unsigned char threshold) {
    for (auto& row : image) {
        for (auto& pixel : row) {
            unsigned char gray = (pixel.r + pixel.g + pixel.b) / 3;
            if (gray > threshold) {
                pixel.r = pixel.g = pixel.b = 255;
            }
            else {
                pixel.r = pixel.g = pixel.b = 0;
            }
        }
    }
}

// Blur Filter (simple average blur)
void blur_filter(std::vector<std::vector<Pixel>>& image) {
    std::vector<std::vector<Pixel>> copy = image;
    int height = image.size();
    int width = image[0].size();

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            image[i][j].r = (copy[i - 1][j - 1].r + copy[i - 1][j].r + copy[i - 1][j + 1].r +
                copy[i][j - 1].r + copy[i][j].r + copy[i][j + 1].r +
                copy[i + 1][j - 1].r + copy[i + 1][j].r + copy[i + 1][j + 1].r) / 9;

            image[i][j].g = (copy[i - 1][j - 1].g + copy[i - 1][j].g + copy[i - 1][j + 1].g +
                copy[i][j - 1].g + copy[i][j].g + copy[i][j + 1].g +
                copy[i + 1][j - 1].g + copy[i + 1][j].g + copy[i + 1][j + 1].g) / 9;

            image[i][j].b = (copy[i - 1][j - 1].b + copy[i - 1][j].b + copy[i - 1][j + 1].b +
                copy[i][j - 1].b + copy[i][j].b + copy[i][j + 1].b +
                copy[i + 1][j - 1].b + copy[i + 1][j].b + copy[i + 1][j + 1].b) / 9;
        }
    }
}

// Sharpen Filter (simple edge sharpen)
void sharpen_filter(std::vector<std::vector<Pixel>>& image) {
    std::vector<std::vector<Pixel>> copy = image;
    int height = image.size();
    int width = image[0].size();

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            int r = (copy[i][j].r * 5 - copy[i - 1][j].r - copy[i + 1][j].r - copy[i][j - 1].r - copy[i][j + 1].r);
            int g = (copy[i][j].g * 5 - copy[i - 1][j].g - copy[i + 1][j].g - copy[i][j - 1].g - copy[i][j + 1].g);
            int b = (copy[i][j].b * 5 - copy[i - 1][j].b - copy[i + 1][j].b - copy[i][j - 1].b - copy[i][j + 1].b);

            image[i][j].r = std::clamp(r, 0, 255);
            image[i][j].g = std::clamp(g, 0, 255);
            image[i][j].b = std::clamp(b, 0, 255);
        }
    }
}

// Sepia Tone Filter
void sepia_filter(std::vector<std::vector<Pixel>>& image) {
    for (auto& row : image) {
        for (auto& pixel : row) {
            unsigned char r = pixel.r;
            unsigned char g = pixel.g;
            unsigned char b = pixel.b;

            pixel.r = std::min(255, (int)(0.393 * r + 0.769 * g + 0.189 * b));
            pixel.g = std::min(255, (int)(0.349 * r + 0.686 * g + 0.168 * b));
            pixel.b = std::min(255, (int)(0.272 * r + 0.534 * g + 0.131 * b));
        }
    }
}

// Apply multiple filters in a pipeline
void apply_pipeline(std::vector<std::vector<Pixel>>& image, const std::vector<FilterFunction>& filters) {
    for (const auto& filter : filters) {
        filter(image); // Apply each filter sequentially
    }
}

// PPM Image processing with a filter pipeline
void process_ppm_image_with_pipeline(const std::string& input_file, const std::string& output_file, const std::vector<FilterFunction>& filters) {
    std::ifstream image_file(input_file, std::ios::binary);
    if (!image_file.is_open()) {
        std::cerr << "Error: Unable to open input PPM file." << std::endl;
        return;
    }

    std::string header;
    int width, height, max_color_value;

    // Reading the PPM file header
    image_file >> header;
    if (header != "P6") {
        std::cerr << "Error: Unsupported PPM format!" << std::endl;
        return;
    }
    image_file >> width >> height >> max_color_value;
    image_file.ignore();  // Skip single whitespace character after the header

    std::vector<std::vector<Pixel>> image(height, std::vector<Pixel>(width));

    // Reading pixel data
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            image_file.read(reinterpret_cast<char*>(&image[i][j]), sizeof(Pixel));
        }
    }

    image_file.close();

    // Apply the filter pipeline
    apply_pipeline(image, filters);

    // Write the processed image back to the output file
    std::ofstream output_image(output_file, std::ios::binary);
    output_image << "P6\n" << width << " " << height << "\n" << max_color_value << "\n";
    for (const auto& row : image) {
        for (const auto& pixel : row) {
            output_image.write(reinterpret_cast<const char*>(&pixel), sizeof(Pixel));
        }
    }
    output_image.close();
}

int main() {
    const std::string ppm_input_file = "imageP6.ppm";
    const std::string output_file_ppm = "output_ppm_pipeline.ppm";

    // Define the filter pipeline (can add or remove filters as needed)
    std::vector<FilterFunction> filter_pipeline = {
        grayscale_filter,
        invert_filter,
       [](std::vector<std::vector<Pixel>>& img) { brightness_filter(img, 50); }, // Adjust brightness
       [](std::vector<std::vector<Pixel>>& img) { contrast_filter(img, 1.5); }, // Adjust contrast
       [](std::vector<std::vector<Pixel>>& img) { threshold_filter(img, 128); }, // Threshold
        blur_filter,
        sharpen_filter,
        sepia_filter
    };

    // Process the PPM image using the filter pipeline
    auto start_time = std::chrono::high_resolution_clock::now();
    process_ppm_image_with_pipeline(ppm_input_file, output_file_ppm, filter_pipeline);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;
    std::cout << "PPM with pipeline processing time: " << duration.count() << " seconds\n";

    return 0;
}
