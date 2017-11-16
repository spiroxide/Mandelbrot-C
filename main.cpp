#include <cstdio>

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

int main() {
    int width = 250;
    int height = 250;
    FILE *file = fopen("Mandelbrot.txt", "w");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int val = mandelbrotValue(mapRange(x, 0, width, -2, 2), mapRange(y, 0, height, -2, 2), 9);
            if (val == 0) {
                fprintf(file, " ");
            }
            else {
                fprintf(file, "%d", val);
            }
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return 0;
}