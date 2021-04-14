#include <iostream>
#include "lodepng.h"

int main() {
    std::vector<unsigned char> png;
    std::vector<unsigned char> image; //the raw pixels
    unsigned int width, height;

    //load and decode
    unsigned int error = lodepng::load_file(png, "/home/vh/Apply1C/input/image.png");
    if (!error) {
        error = lodepng::decode(image, width, height, png);
    }

    //if there's an error, display it
    if (error) {
        std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    } else {
        std::cout << width << " " << height;
    }



    return 0;
}
