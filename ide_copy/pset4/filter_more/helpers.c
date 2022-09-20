#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j, avg;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            //calculating avg
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (float)3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int i, l, u;
    //l = lower_limit
    //u = upper_limit
    RGBTRIPLE temp;
    for (i = 0; i < height; i++)
    {
        l = 0;
        u = width - 1;
        while (u > l)
        {
            //swapping until u > l
            //temp of type RGBTRIPLE
            temp = image[i][l];
            image[i][l] = image[i][u];
            image[i][u] = temp;

            //increasing u and decreasing l
            u--;
            l++;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int i, j, ic, jc, sumBlue = 0, sumGreen = 0, sumRed = 0, c = 0;

    // Creating copy of type RGBTRIPLE image
    // Mutating in place can lead to side effects
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            //Re initializing all temporary variables
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            c = 0;

            //generating all possible combinations [i - 1 -> i + 1] :: [j - 1 -> j + 1]
            for (ic = i - 1; ic <= (i + 1); ic++)
            {
                for (jc = j - 1; jc <= (j + 1); jc++)
                {
                    //if values lie in range. ref: height, width
                    if ((ic >= 0 && ic < height) && (jc >= 0 && jc < width))
                    {
                        // Calculating sum using original image
                        sumBlue += image[ic][jc].rgbtBlue;
                        sumGreen += image[ic][jc].rgbtGreen;
                        sumRed += image[ic][jc].rgbtRed;
                        c++;
                    }
                }
            }
            //calculating avg
            //mutating copy image only
            copy[i][j].rgbtBlue = round(sumBlue / (float)c);
            copy[i][j].rgbtGreen = round(sumGreen / (float)c);
            copy[i][j].rgbtRed = round(sumRed / (float)c);

        }
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE copy[height][width];
    int i, j, ic, jc, ki, kj, g_r, g_g, g_b;

    // Creating specific gx and gy for RGB for convenience
    int g_x_r, g_x_g, g_x_b;
    int g_y_r, g_y_g, g_y_b;


    // Creating copy of type RGBTRIPLE image
    // Mutating in place can lead to side effects
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            //Re initializing all temporary variables
            g_x_r = 0;
            g_x_g = 0;
            g_x_b = 0;
            g_y_r = 0;
            g_y_g = 0;
            g_y_b = 0;
            //generating all possible combinations [i - 1 -> i + 1] :: [j - 1 -> j + 1]
            for (ki = -1; ki < 2; ki++)
            {
                for (kj = -1; kj < 2; kj++)
                {
                    ic = i + ki;
                    jc = j + kj;
                    //if values lie in range. ref: height, width
                    if ((ic >= 0 && ic < height) && (jc >= 0 && jc < width))
                    {
                        // Computing In X direction
                        g_x_r += image[ic][jc].rgbtRed * Gx[ki + 1][kj + 1];
                        g_x_g += image[ic][jc].rgbtGreen * Gx[ki + 1][kj + 1];
                        g_x_b += image[ic][jc].rgbtBlue * Gx[ki + 1][kj + 1];

                        g_y_r += image[ic][jc].rgbtRed * Gy[ki + 1][kj + 1];
                        g_y_g += image[ic][jc].rgbtGreen * Gy[ki + 1][kj + 1];
                        g_y_b += image[ic][jc].rgbtBlue * Gy[ki + 1][kj + 1];
                    }
                }
            }

            g_r = round(sqrt(pow(g_x_r, 2) + pow(g_y_r, 2)));
            g_g = round(sqrt(pow(g_x_g, 2) + pow(g_y_g, 2)));
            g_b = round(sqrt(pow(g_x_b, 2) + pow(g_y_b, 2)));

            copy[i][j].rgbtRed = (g_r > 255) ? 255 : g_r;
            copy[i][j].rgbtGreen = (g_g > 255) ? 255 : g_g;
            copy[i][j].rgbtBlue = (g_b > 255) ? 255 : g_b;
        }
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }

    return;
}
