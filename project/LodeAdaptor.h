#include <string>
#include <utility>
#include <vector>
#include <cassert>
#include "lodepng.h"
#include "GameMap.h"
#include <iostream>

namespace vh {

    class LodeImageAdaptor {
    public:
        explicit LodeImageAdaptor(std::string file_name) : file_(std::move(file_name)) {}

        void Load() {

            assert(!loaded_);
            std::vector<unsigned char> png;
            std::vector<unsigned char> image; //the raw pixels
            unsigned width, height;
            lodepng::State state; //optionally customize this one

            unsigned error = lodepng::load_file(png, file_); //load the image file with given filename
            assert(!error);
            error = lodepng::decode(image, width, height, state, png);
            assert(!error);
            loaded_ = true;
            width_ = width;
            height_ = height;
            image_ = std::move(image);
            Make2DArray(image_);

        }

        std::vector<unsigned char> &operator[](size_t i) {
            return array2d_[i];
        }

        size_t Height() {
            return height_;
        }

        size_t Width() {
            return width_;
        }

        void DrawWinLineAndSave(
                recognizer::GameMap& mp,
                const std::string& outfile,
                size_t top,
                size_t left,
                size_t square_size
        ) {
            /* Diagonals */
            CheckNDraw(mp, {{2, 0}, {1, 1}, {0, 2}}, top, left, square_size);
            CheckNDraw(mp, {{0, 0}, {1, 1}, {2, 2}}, top, left, square_size);
            /* Lines */
            CheckNDraw(mp, {{0, 0}, {0, 1}, {0, 2}}, top, left, square_size);
            CheckNDraw(mp, {{1, 0}, {1, 1}, {1, 2}}, top, left, square_size);
            CheckNDraw(mp, {{2, 0}, {2, 1}, {2, 2}}, top, left, square_size);
            /* Columns */
            CheckNDraw(mp, {{0, 0}, {1, 0}, {2, 0}}, top, left, square_size);
            CheckNDraw(mp, {{0, 1}, {1, 1}, {2, 1}}, top, left, square_size);
            CheckNDraw(mp, {{0, 2}, {1, 2}, {2, 2}}, top, left, square_size);
            SaveImage(outfile);
        }

        void SaveImage(const std::string& outfile) {
            std::vector<unsigned char> png;
            unsigned error = lodepng::encode(png, image_, width_, height_);
            assert(!error);
            lodepng::save_file(png, outfile);
        }

    private:

        void CheckNDraw(
                recognizer::GameMap& mp,
                const std::vector<std::pair<size_t, size_t> >& to_check,
                size_t top,
                size_t left,
                size_t square_size
        ) {
            if (mp[to_check[0].first][to_check[0].second] == recognizer::empty) {
                return;
            }
            if (
                mp[to_check[0].first][to_check[0].second] == mp[to_check[1].first][to_check[1].second] &&
                mp[to_check[1].first][to_check[1].second] == mp[to_check[2].first][to_check[2].second]
            ) {
                for (auto& el : to_check) {
                    DrawLineCell(top, left, square_size, el.first, el.second);
                }
            }
        }

        void DrawLineCell(
            size_t top,
            size_t left,
            size_t square_size,
            size_t line,
            size_t column
        ) {
            DrawLine(
                    top + line * square_size + square_size / 2,
                    left + column * square_size,
                    square_size,
        4);
        }

        void DrawLine(size_t x, size_t y, size_t length, size_t width) {
            for (size_t i = x; i < x + width; ++i) {
                for (size_t j = y; j < y + length; ++j) {
                   image_[i * width_ * 4 + j * 4] = 255;
                   image_[i * width_ * 4 + j * 4 + 1] = 0;
                   image_[i * width_ * 4 + j * 4 + 2] = 0;
                }
            }
        }

        void Make2DArray(std::vector<unsigned char> &image) {
            assert(image.size() / 4 == width_ * height_);
            array2d_.assign(height_, std::vector<unsigned char>(width_));
            size_t count = image.size() / 4;
            for (size_t i = 0; i < count; ++i) {
                size_t r = image[i * 4];
                size_t g = image[i * 4 + 1];
                size_t b = image[i * 4 + 2];
                array2d_[i / width_][i % width_] = r + g + b < 100 ? 1 : 0;
            }
        }

        std::vector<std::vector<unsigned char> > array2d_;
        size_t width_{};
        size_t height_{};
        std::string file_;
        bool loaded_{false};
        std::vector<unsigned char> image_; //the raw pixels
    };

}
