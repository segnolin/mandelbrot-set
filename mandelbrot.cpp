#include <iostream>
#include <cmath>
#include <thread>

#define DIM 8192
#define THREAD 8

#define X -0.5
#define Y 0
#define RADIUS 2.5
#define STEP 64
#define MAX_ITERATIONS 196

using namespace std;

FILE *fp;
unsigned char Canvas[DIM][DIM][3];
int progress = 0;
unsigned char palette[16][3] = {{30, 16, 48}, {15, 12, 94}, {3, 28, 150}, {6, 50, 188},
                                {20, 80, 195}, {57, 125, 209}, {73, 155, 216}, {134, 181, 229},
                                {170, 210, 235}, {240, 249, 250}, {246, 231, 161}, {252, 212, 70},
                                {251, 175, 42}, {215, 126, 41}, {187, 79, 39}, {110, 50, 53}};

void Mandelbrot(int threadNum);
void setColor(int iteration, unsigned char *color);
void LinearInterpolate(unsigned char *color, unsigned char *color1, unsigned char *color2, double fractional);
void logColor(int i, int j, unsigned char *color);
void drawPixel();
void updateProgress(int threadNum);

int main()
{
    fp = fopen("mandelbrot.ppm" ,"wb");
    fprintf(fp, "P6\n%d %d\n255\n", DIM, DIM);
    thread t[THREAD];
    for (int i = 0; i < THREAD; ++i) {
        t[i] = thread(Mandelbrot, i);
    }
    for (int i = 0; i < THREAD; ++i) {
        t[i].join();
    }
    drawPixel();
    fclose(fp);
    cout << "\rMandelbrot calculating - 100% [Finished]\n";
    return 0;
}

void Mandelbrot(int threadNum)
{
    for (int j = 0; j < DIM; ++j) {
        updateProgress(threadNum);
        for (int i = threadNum; i < DIM; i += THREAD) {
            double x0 = X - RADIUS + 2 * RADIUS * i / DIM;
            double y0 = -Y - RADIUS + 2 * RADIUS * j / DIM;
            double x = 0;
            double y = 0;
            int iteration = 0;
            while (x * x + y * y < 16 && iteration < MAX_ITERATIONS) {
                double xtemp = x * x - y * y + x0;
                y = 2 * x * y + y0;
                x = xtemp;
                ++iteration;
            }
            double iterationF = iteration;
            if (iterationF < MAX_ITERATIONS) {
                double log_zn = log(x * x + y * y) / 2;
                double nu = log(log_zn / log(2)) / log(2);
                iterationF = iterationF + 1 - nu;
            }
            unsigned char color[3];
            unsigned char color1[3];
            unsigned char color2[3];
            setColor(floor(iterationF), color1);
            setColor(floor(iterationF) + 1, color2);
            LinearInterpolate(color, color1, color2, iterationF - (int)iterationF);
            logColor(i, j, color);
        }
    }
}

void setColor(int iteration, unsigned char *color)
{
    if (0 < iteration && iteration < MAX_ITERATIONS) {
        double hue = (double)(iteration % STEP) / STEP;
        int n = 0;
        while (hue > 0.0625) {
            hue -= 0.0625;
            ++n;
        }
        unsigned char color1[3];
        unsigned char color2[3];
        for (int i = 0; i < 3; ++i) {
            color1[i] = palette[n][i];
            color2[i] = palette[(n + 1) % 16][i];
        }
        LinearInterpolate(color, color1, color2, hue / 0.0625);
    }
    else {
        color[0] = 0; color[1] = 0; color[2] = 0;
    }
}

void LinearInterpolate(unsigned char *color, unsigned char *color1, unsigned char *color2, double fractional)
{
    for (int i = 0; i < 3; ++i) {
        color[i] = color1[i] * (1 - fractional) + color2[i] * fractional;
    }
}

void logColor(int i, int j, unsigned char *color)
{
    for (int k = 0; k < 3; ++k) {
        Canvas[i][j][k] = color[k];
    }
}

void drawPixel()
{
    for (int j = 0; j < DIM; ++j) {
        for (int i = 0; i < DIM; ++i) {
            fwrite(Canvas[i][j], 1, 3, fp);
        }
    }
}

void updateProgress(int threadNum)
{
    if (!threadNum) {
        progress += 1;
        cout.flush();
        cout << "\rMandelbrot calculating - " << 100 * progress / DIM << "%";
    }
}
