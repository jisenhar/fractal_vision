#ifndef FRACTALGEN_H
#define FRACTALGEN_H
#include <cstdint>

class FractalGenerator{
        public:
                virtual void fillBuffer(uint32_t frame[], int height, int width)=0;
};

#endif
