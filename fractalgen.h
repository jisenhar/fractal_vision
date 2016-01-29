#ifndef FRACTALGEN_H
#define FRACTALGEN_H
#include <cstdint>

class FractalGenerator{
        public:
                virtual void fillBuffer(uint32_t* frame, int height, int width)=0;
                virtual void increaseZoom()=0;
                virtual void decreaseZoom()=0;
                virtual void panY(int direction)=0;
                virtual void panX(int direction)=0;
};

#endif
