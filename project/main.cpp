#include <iostream>
#include "recognizer.h"

int main() {

    vh::LodeImageAdaptor image("/home/vh/Apply1C/input/test2.png");
    image.Load();

    recognizer::Recognizer map_recognizer(image);

    recognizer::GameMap mp = std::move(map_recognizer.RecognizeMap());
    for (auto & x : mp) {
        for (auto & y : x) {
            std::cout << y;
        }
        std::cout << std::endl;
    }
    image.DrawWinLineAndSave(
        mp,
        "/home/vh/Apply1C/input/out2.png",
        map_recognizer.GetTop(),
        map_recognizer.GetLeft(),
        map_recognizer.GetSquareSize()
    );

    return 0;
}
