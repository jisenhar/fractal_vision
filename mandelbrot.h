#ifndef MANDELBROT_H
#define MANDELBROT_H
#include "fractalgen.h"
#include <cstdint>

class MandelbrotGenerator: public FractalGenerator{
        public:
                void fillBuffer(uint32_t frame[], int height, int width);
        private:
                int max_iterations = 1000;
                int escapeTime(int row, int col, int height, int width);
                uint32_t getColor(int escape_time);
};
#endif
