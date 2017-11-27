#include <cstdio>
#include <sstream>
#include <fstream>

using namespace std;

int mandelbrotValue(double real, double imaginary, int maxIterations) {
    double a = real;
    double b = imaginary;

    int i = 0;
    while (i < maxIterations) {
        double ab = a * b;

        a = a * a - b * b + real;
        b = 2 * ab + imaginary;

        if (a * a + b * b > 4) {
            break;
        }
        i++;
    }
    return i;
}

double mapRange(double valF, double startF, double endF, double startT, double endT) {
    return (endT - startT) / (endF - startF) * (valF - startF) + startT;
}

const int WIDTH = 512, HEIGHT = 512, MAX_ITERATIONS = 100;

int main() {
    for (int i = 0; i < 260; i += 10) {
        string path = "images/mandelbrot" + to_string(i) + ".ppm";
        ofstream mandelbrotPPM(path);
        mandelbrotPPM << "P3" << endl;
        mandelbrotPPM << HEIGHT << " " << WIDTH << endl;
        mandelbrotPPM << "255" << endl;
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                int val = mandelbrotValue(mapRange(x, 0, WIDTH, -2.5, 1.5), mapRange(y, 0, HEIGHT, -2, 2),
                                          MAX_ITERATIONS);
                int r = (val + x + i) % 256;
                int g = (val + y + i) % 256;
                int b = (val + (x * y) + i) % 256;
                mandelbrotPPM << r << " " << g << " " << b << endl;
            }
        }
    }
    return 0;
}