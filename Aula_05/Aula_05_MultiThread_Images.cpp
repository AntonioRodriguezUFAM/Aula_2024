#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./stb_image/stb_image.h"
#include "./stb_image/stb_image_write.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstring>




struct Pixel {
    unsigned char r, g, b;
};

const std::string jpg_input_file = "apple.jpg";
const std::string ppm_input_file = "apollo.ppm";
const std::string output_file_ppm = "output_ppm.ppm";
const std::string output_file_stb = "output_stb.jpg";

// Function to apply a filter (e.g., grayscale) on a region of the image
void apply_filter(std::vector<std::vector<Pixel>>& image, int start_row, int end_row) {
    for (int i = start_row; i < end_row; ++i) {
        for (int j = 0; j < image[i].size(); ++j) {
            unsigned char gray = (image[i][j].r + image[i][j].g + image[i][j].b) / 3;
            image[i][j].r = gray;
            image[i][j].g = gray;
            image[i][j].b = gray;
        }
    }
}

// Function to read PPM image
void process_ppm_image(const std::string& input_file, const std::string& output_file) {
    std::ifstream image_file(input_file, std::ios::binary);
    if (!image_file.is_open()) {
        std::cerr << "Error: Unable to open input PPM file." << std::endl;
        return;
    }

    std::string header;
    int width, height, max_color_value;

    // Reading the PPM file header
    image_file >> header;
    if (header != "P3") {
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

    // Apply the grayscale filter
    apply_filter(image, 0, height);

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

// Using STB Image for other formats like JPG
void process_stb_image(const std::string& input_file, const std::string& output_file) {
    int width, height, channels;
    //unsigned char* data = stbi_load(filename, &x, &y, &n, 0);
    unsigned char* data = stbi_load(jpg_input_file.c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Error loading image: " << stbi_failure_reason() << std::endl;
        return;
    }

    // Convert to vector of pixels
    std::vector<std::vector<Pixel>> image(height, std::vector<Pixel>(width));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int idx = (i * width + j) * channels;
            image[i][j] = { data[idx], data[idx + 1], data[idx + 2] };
        }
    }

    // Apply the filter
    apply_filter(image, 0, height);

    // Convert back to unsigned char* for STB
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int idx = (i * width + j) * channels;
            data[idx] = image[i][j].r;
            data[idx + 1] = image[i][j].g;
            data[idx + 2] = image[i][j].b;
        }
    }

    // Write the processed image
    stbi_write_jpg(output_file.c_str(), width, height, channels, data, 100);

    stbi_image_free(data);
}

// Multithreaded version
void process_stb_image_multithreaded(const std::string& input_file, const std::string& output_file, int num_threads) {
    int width, height, channels;
    unsigned char* data = stbi_load(input_file.c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Error loading image: " << stbi_failure_reason() << std::endl;
        return;
    }

    // Convert to vector of pixels
    std::vector<std::vector<Pixel>> image(height, std::vector<Pixel>(width));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int idx = (i * width + j) * channels;
            image[i][j] = { data[idx], data[idx + 1], data[idx + 2] };
        }
    }

    // Divide the image into regions and create threads
    int rows_per_region = height / num_threads;
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        int start_row = i * rows_per_region;
        int end_row = (i == num_threads - 1) ? height : (i + 1) * rows_per_region;
        threads.emplace_back(apply_filter, std::ref(image), start_row, end_row);
    }

    // Wait for threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    // Convert back to unsigned char* for STB
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int idx = (i * width + j) * channels;
            data[idx] = image[i][j].r;
            data[idx + 1] = image[i][j].g;
            data[idx + 2] = image[i][j].b;
        }
    }

    // Write the processed image
    stbi_write_jpg(output_file.c_str(), width, height, channels, data, 100);

    stbi_image_free(data);
}

int main() {


    // Measure time for PPM
    auto start_time = std::chrono::high_resolution_clock::now();
    process_ppm_image(ppm_input_file, output_file_ppm);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_ppm = end_time - start_time;
    std::cout << "PPM time: " << duration_ppm.count() << " seconds\n";

    // Measure time for STB Image (single-threaded)
    start_time = std::chrono::high_resolution_clock::now();
    process_stb_image(jpg_input_file, output_file_stb);
    end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_stb_single = end_time - start_time;
    std::cout << "STB Image (single-threaded) time: " << duration_stb_single.count() << " seconds\n";

    // Measure time for STB Image (multithreaded)
    start_time = std::chrono::high_resolution_clock::now();
    process_stb_image_multithreaded(jpg_input_file, output_file_stb, 4); // Adjust num_threads
    end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_stb_multi = end_time - start_time;
    std::cout << "STB Image (multithreaded) time: " << duration_stb_multi.count() << " seconds\n";

    return 0;
}
