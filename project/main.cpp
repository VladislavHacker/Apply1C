#include <iostream>
#include "recognizer.h"

int main(int argc, char** argv) {
    assert(argc == 3);
    std::string input_file(argv[1]);
    std::string output_file(argv[2]);
    vh::LodeImageAdaptor image(input_file);
    image.Load();

    recognizer::Recognizer map_recognizer(image);

    recognizer::GameMap mp = std::move(map_recognizer.RecognizeMap());

    image.DrawWinLineAndSave(
        mp,
        output_file,
        map_recognizer.GetTop(),
        map_recognizer.GetLeft(),
        map_recognizer.GetSquareSize()
    );

    return 0;
}
