#include <complex>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include "Mandelbrot.h"


using namespace std;

MandelbrotGenerator::MandelbrotGenerator(){
}

/**
        Fills buffer with colors of a Mandelbrot set of given height and width
        @param frame[] Start of frame buffer array
        @param height Height of Mandelbrot set
        @param width Width of Mandelbrot set
*/
void MandelbrotGenerator::fillBuffer(uint32_t* frame, int height, int width){
        int row, col, i;
        i=0;
        // cout <<  "mandelbrot" << endl;
        for(row=0; row<height; row++){
                // cout << endl;
                for(col=0; col<width; col++){
                        int time = escapeTime(row, col, height, width);
                        frame[i] = getColor(time);
                       /* uint32_t RGB = frame[i];
                        uint8_t r = RGB >> 24;
                        uint8_t g = RGB >> 16;
                        uint8_t b = RGB >> 8;
                        cout << '(' << int(r) << ' ' << int(g) << ' ' << int(b) << ") ";*/
                        i++;
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

void MandelbrotGenerator::updateColorTable(int height, int width){
        std::cout << "Entering color table\n";
        uint32_t *test_frame;
        test_frame = new uint32_t [height*width];
        int histogram[max_iterations+1] = {0};
        int row, col, i, j;
        i=0;
        int total_iterations = 0;
        for(row=0; row<height; row++){
                for(col=0; col<width; col++){
                        int time = escapeTime(row, col, height, width);
                        test_frame[i] = time;
                        histogram[time]++;
                        i++;
                        total_iterations += time;
                }
        }
        total_iterations -= histogram[max_iterations]*max_iterations;

        uint8_t start_red = 255, start_green = 175, start_blue = 25;
        uint8_t end_red = 0, end_green = 255, end_blue = 255;
        uint8_t red_change = end_red - start_red;
        uint8_t green_change = end_green - start_green;
        uint8_t blue_change = end_blue - start_blue;
        
        int running_total = 0;
        uint8_t r = start_red;
        uint8_t g = start_green;
        uint8_t b = start_blue;
        uint32_t color;
        for(j=0; j<=max_iterations; j++){
                running_total += (histogram[j]*(j));
                double percent = (double)running_total/(double)total_iterations;
                cout << percent << '\n';
                cout << running_total << ' ' << total_iterations << '\n';
                if(j==max_iterations){
                        r = 0;
                        g = 0;
                        b = 0;
                }
                else{
                        r = start_red + (int)red_change*percent;
                        g =  start_green + (int)green_change*percent;
                        b =  start_blue + (int)blue_change*percent;
                }
                cout << '(' << int(r) << ' ' << int(g) << ' ' << int(b) << ") ";
                color = r;
                color = (color << 8) + g;
                color = (color << 8) + b;
                color = (color << 8) + 0; //alpha
                colorTable[j] = color;
        }
        colorTableSet = true;
}

/**
        Gets a RGB color from an escape time number of iterations
        @param escape_time Escape time of point
        @return 32-bit word containing an RGB color, r in high 8 bits, b next, g, next, alpha in low 8 bits
*/
uint32_t MandelbrotGenerator::getColor(int escape_time){


        if(colorTableSet){
                return colorTable[escape_time];
        }
        else{
               // std::cout << "using other colors";
                uint8_t alpha = 0; //Don't give a fuck about alpha
                uint8_t r;
                uint8_t b;
                uint8_t g;
               /* double ratio = (2*(double)escape_time)/max_iterations;
                uint8_t r = (uint8_t)max(0.0, 255*(ratio-1)); //Red on one side
                uint8_t b = (uint8_t)max(0.0, 255*(1-ratio)); //Blue on the other
                uint8_t g = 255-b-r; //And green in the middle**/
                if(escape_time <= 10){
                        r = 255;
                        g = 0;
                        b = 0;
                }
                else if(10 < escape_time && escape_time <= 20){
                        r = 255;
                        g = 127;
                        b = 0;
                }
                else if(20 < escape_time && escape_time <= 30){
                        r = 255;
                        g = 255;
                        b = 0;
                }
                else if( 30 < escape_time && escape_time <= 40){
                        r = 127;
                        g = 255;
                        b = 0;
                }
                else if(40 < escape_time && escape_time <= 50){
                        r = 0;
                        g = 255;
                        b = 0;
                }
                else if(50 < escape_time && escape_time <= 60){
                        r = 0;
                        g = 255;
                        b = 127;
                }
                else if(60 < escape_time && escape_time <= 70){
                        r = 0;
                        g = 255;
                        b = 255;
                }
                else if(70 < escape_time && escape_time <= 80){
                        r = 0;
                        g = 0;
                        b = 255;
                        }
                else if(80 < escape_time && escape_time <= 90){
                        r = 127;
                        g = 0;
                        b = 255;
                        }
                else if(90 < escape_time && escape_time < 100){
                        r = 255;
                        g = 0;
                        b = 255;
                        }
                else{
                        r = 0;
                        g = 0;
                        b = 0;
                }
                uint32_t color = r; //And shift them all into a 32-bit word
                color = (color << 8) + b;
                color = (color << 8) + g;
                color = (color << 8) + alpha;
                return color;
        }

}
