#include <iostream>
#include <complex>
#include <cstdint>
#include <algorithm>
#include "Mandelbrot.h"


using namespace std;

/**
        Fills buffer with colors of a Mandelbrot set of given height and width
        @param frame[] Start of frame buffer array
        @param height Height of Mandelbrot set
        @param width Width of Mandelbrot set
*/
void MandelbrotGenerator::fillBuffer(uint32_t frame[], int height, int width){
                        int row, col;
                        for(row=0; row<height; row++){
                                for(col=0; col<width; col++){
                                        int time = escapeTime(row, col, height, width);
                                        frame[row+col] = getColor(time);
                                }
                        }
                }

/**
        Calculates the escape time in number of iterations of the given point in the Mandelbrot set.
        (Every point will either converge and stay under 2 or diverge. Calculates how long it takes to
        diverge, if it does so at all)
        @param row Row of point to calculate
        @param col Column of point to calculate
        @param height Height of Mandelbrot set
        @param width Width of Mandelbrot set
        @return number of iterations to escape in, max_iterations if convergence
*/
int MandelbrotGenerator::escapeTime(int row, int col, int height, int width){
        complex<double> I(0, 1); //Define i, because C++ complex numbers are kinda gross
        complex<double> c = ((double)((double)col/width)*3.5-2.5) + ((double)((double)row/height) -.5) * 2*I; //Formula from the pset
        complex<double> z_prev(0,0);
        int i;
        int iteration = 0;
        //Continue to calculate z until we see it diverge, or hit max iterations
        for(i=0; i<max_iterations; i++){
                z_prev = z_prev*z_prev+c;
                if(real(conj(z_prev)*z_prev) >= 4.0){
                        return iteration;       
                }
                iteration += 1;
        }
        return max_iterations;
}

/**
        Gets a RGB color from an escape time number of iterations
        @param escape_time Escape time of point
        @return 32-bit word containing an RGB color, r in high 8 bits, b next, g, next, alpha in low 8 bits
*/
uint32_t MandelbrotGenerator::getColor(int escape_time){
        double ratio = (2*(double)escape_time)/max_iterations;
        uint8_t r = (uint8_t)max(0.0, 255*(ratio-1)); //Red on one side
        uint8_t b = (uint8_t)max(0.0, 255*(1-ratio)); //Blue on the other
        uint8_t g = 255-b-r; //And green in the middle
        uint8_t alpha = 0; //Don't give a fuck about alpha
        uint32_t color = r; //And shift them all into a 32-bit word
        color = (color << 8) + b;
        color = (color << 8) + g;
        color = (color << 8) + alpha;
        return color;        
}

int main(){
}
