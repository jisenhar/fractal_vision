#ifndef MANDELBROT_H
#define MANDELBROT_H
#include "fractalgen.h"

class MandelbrotGenerator: public FractalGenerator{
        public:
                void fillBuffer(uint32_t* frame, int height, int width);
                void updateColorTable(int height, int width);
                MandelbrotGenerator();

        protected:
                static const int max_iterations = 100;
                int escapeTime(int row, int col, int height, int width);
                uint32_t getColor(int escape_time);

        private:
                uint32_t colorTable[max_iterations];
                bool colorTableSet = false;
};
#endif
