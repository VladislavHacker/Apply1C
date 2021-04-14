#include <array>
#include "LodeAdaptor.h"
#include "GameMap.h"

namespace recognizer {

    class Recognizer {
    public:

        explicit Recognizer(vh::LodeImageAdaptor image)
            : img_(std::move(image)),
              top_(FindTop()),
              left_(FindLeft()),
              right_(FindRight()),
              square_size_((right_ - left_ ) / 3)
        {
        }

        GameMap RecognizeMap () {
            size_t top = top_;
            size_t left = left_;
            size_t right = right_;
            size_t symbol_square = square_size_;
            GameMap mp(3);
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    mp[i].emplace_back(RecognizeSymbol(
                        top + symbol_square * i,
                        left + symbol_square * j,
                        symbol_square
                    ));
                }
            }

            return mp;
        }

        size_t GetTop() {
            return top_;
        }

        size_t GetLeft() {
            return left_;
        }

        size_t GetRight() {
            return right_;
        }

        size_t GetSquareSize() {
            return square_size_;
        }

    private:
        size_t FindTop() {
            for (size_t i = 0; i < img_.Height(); ++i) {
                bool check = false;
                for (size_t j = 0; j < img_.Width(); ++j) {
                    if (img_[i][j] == 1) {
                        check = true;
                    }
                }
                if (check) {
                    return i;
                }
            }
            return 0;
        }

        size_t FindRight() {
            for (size_t j = img_.Width() - 1; j >= 0; --j) {
                bool check = false;
                for (size_t i = 0; i < img_.Height(); ++i) {
                    if (img_[i][j] == 1) {
                        check = true;
                    }
                }
                if (check) {
                    return j;
                }
            }
            return 0;
        }

        size_t FindLeft() {
            for (size_t j = 0; j < img_.Width(); ++j) {
                bool check = false;
                for (size_t i = 0; i < img_.Height(); ++i) {
                    if (img_[i][j] == 1) {
                        check = true;
                    }
                }
                if (check) {
                    return j;
                }
            }
            return 0;
        }

        unsigned char RecognizeSymbol(size_t form_i, size_t from_j, size_t square_size) {
            /* check center of the cell for 1 =) */
            size_t start_i = form_i + static_cast<size_t> (0.4 * square_size);
            size_t end_i = form_i + static_cast<size_t> (0.6 * square_size);
            size_t start_j = from_j + static_cast<size_t> (0.4 * square_size);
            size_t end_j = from_j + static_cast<size_t> (0.6 * square_size);
            std::array<size_t, 2> arr = {0 ,0};
            for (size_t i = start_i; i < end_i; ++i) {
                for (size_t j = start_j; j < end_j; ++j) {
                    ++arr[(int)img_[i][j]];
                }
            }

            if (arr[1] > arr[0]) {
                return cross;
            }

            return EmptyOrZero(form_i, from_j, square_size);

        }

        unsigned char EmptyOrZero(size_t form_i, size_t from_j, size_t square_size) {
            size_t i = form_i + square_size / 2;
            bool now_zero = true;
            size_t cnt = 0;
            for (size_t j = from_j; j < from_j + square_size; ++j) {
                if (img_[i][j] == 0) {
                    now_zero = true;
                } else if (now_zero) {
                    now_zero = false;
                    ++cnt;
                }
            }
            if (cnt >= 3) { // 2 bounds of zero and square bound =)
                return zero;
            }
            return empty;
        }

        vh::LodeImageAdaptor img_;
        size_t top_;
        size_t left_;
        size_t right_;
        size_t square_size_;

    };
}
