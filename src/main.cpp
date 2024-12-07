#include "image_generator.h"
#include <iostream>
#include <string>
#include <limits>

// Helper function to get numeric input with validation
template<typename T>
T getNumericInput(const std::string& prompt, T min_val, T max_val) {
    T value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if (value >= min_val && value <= max_val) {
                break;
            }
            std::cout << "Value must be between " << min_val << " and " << max_val << std::endl;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
        }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

// Helper function to get color input
rt::Color<rt::Float> getColorInput(const std::string& colorName) {
    std::cout << "\nEnter " << colorName << " (values between 0.0 and 1.0):\n";
    float r = getNumericInput<float>("Red: ", 0.0f, 1.0f);
    float g = getNumericInput<float>("Green: ", 0.0f, 1.0f);
    float b = getNumericInput<float>("Blue: ", 0.0f, 1.0f);
    return rt::Color<rt::Float>(r, g, b);
}

int main() {
    try {
        // Welcome message
        std::cout << "=== Image Pattern Generator ===\n\n";

        // Get image dimensions
        std::cout << "First, let's set up the image dimensions:\n";
        size_t width = getNumericInput<size_t>("Enter image width (100-4000): ", 100, 4000);
        size_t height = getNumericInput<size_t>("Enter image height (100-4000): ", 100, 4000);

        // Create image generator
        rt::ImageGenerator generator(width, height);

        // Pattern selection
        std::cout << "\nAvailable patterns:\n";
        std::cout << "1. Checker pattern\n";
        std::cout << "2. Droste pattern\n";
        int patternChoice = getNumericInput<int>("Select pattern (1-2): ", 1, 2);

        // Get colors
        rt::Color<rt::Float> color1 = getColorInput("first color");
        rt::Color<rt::Float> color2 = getColorInput("second color");

        // Get pattern-specific parameters and generate pattern
        if (patternChoice == 1) {
            size_t squareSize = getNumericInput<size_t>(
                "Enter square size (10-200): ", 10, 200);
            generator.generateCheckerPattern(squareSize, color1, color2);
        } else {
            float tightness = getNumericInput<float>(
                "Enter spiral tightness (0.01-1.0): ", 0.01f, 1.0f);
            float repetitions = getNumericInput<float>(
                "Enter number of repetitions (1.0-10.0): ", 1.0f, 10.0f);
            generator.generateDrostePattern(tightness, repetitions, color1, color2);
        }

        // Get output filename
        std::string filename;
        std::cout << "\nEnter output filename (will be saved as .ppm): ";
        std::getline(std::cin, filename);
        if (filename.empty()) {
            filename = "output";
        }
        if (filename.substr(filename.length() - 4) != ".ppm") {
            filename += ".ppm";
        }

        // Save the image
        generator.setFilename(filename);
        generator.saveImage();
        std::cout << "\nImage saved successfully as: " << filename << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
