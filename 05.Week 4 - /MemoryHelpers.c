#include "helpers.h"
#include <math.h>
#include <stdint.h>

// Convert image to grayscale
// Each pixel's R, G, B set to the rounded average of the original three
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = (int)round(((double)image[i][j].rgbtRed +
                                  (double)image[i][j].rgbtGreen +
                                  (double)image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed   = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue  = avg;
        }
    }
}

// Reflect image horizontally
// Swap pixels at column j and column (width - 1 - j) in each row
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp        = image[i][j];
            image[i][j]          = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// Blur image using 3x3 box blur
// Each pixel becomes the average of itself and all valid neighbours
// Uses a temporary copy so we always read original values
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Stack-allocate a copy of the original image
    RGBTRIPLE original[height][width];
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            original[i][j] = image[i][j];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float totalR = 0, totalG = 0, totalB = 0;
            int count = 0;

            // Check all 9 cells in the 3x3 kernel around (i, j)
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        totalR += original[ni][nj].rgbtRed;
                        totalG += original[ni][nj].rgbtGreen;
                        totalB += original[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            image[i][j].rgbtRed   = (int)round(totalR / count);
            image[i][j].rgbtGreen = (int)round(totalG / count);
            image[i][j].rgbtBlue  = (int)round(totalB / count);
        }
    }
}

// Detect edges using the Sobel operator
// Gx and Gy kernels applied per-channel; final value = min(255, sqrt(Gx^2 + Gy^2))
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Sobel kernels
    int Kx[3][3] = {{-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}};

    int Ky[3][3] = {{-1, -2, -1},
                    { 0,  0,  0},
                    { 1,  2,  1}};

    // Work on a copy so we always read original pixel values
    RGBTRIPLE original[height][width];
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            original[i][j] = image[i][j];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int GxR = 0, GxG = 0, GxB = 0;
            int GyR = 0, GyG = 0, GyB = 0;

            // Apply both kernels across the 3x3 neighbourhood
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Treat out-of-bounds pixels as 0 (black)
                    int r = 0, g = 0, b = 0;
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        r = original[ni][nj].rgbtRed;
                        g = original[ni][nj].rgbtGreen;
                        b = original[ni][nj].rgbtBlue;
                    }

                    GxR += Kx[di + 1][dj + 1] * r;
                    GxG += Kx[di + 1][dj + 1] * g;
                    GxB += Kx[di + 1][dj + 1] * b;

                    GyR += Ky[di + 1][dj + 1] * r;
                    GyG += Ky[di + 1][dj + 1] * g;
                    GyB += Ky[di + 1][dj + 1] * b;
                }
            }

            // Compute magnitude for each channel, cap at 255
            int edgeR = (int)round(sqrt(GxR * GxR + GyR * GyR));
            int edgeG = (int)round(sqrt(GxG * GxG + GyG * GyG));
            int edgeB = (int)round(sqrt(GxB * GxB + GyB * GyB));

            image[i][j].rgbtRed   = edgeR > 255 ? 255 : edgeR;
            image[i][j].rgbtGreen = edgeG > 255 ? 255 : edgeG;
            image[i][j].rgbtBlue  = edgeB > 255 ? 255 : edgeB;
        }
    }
}
