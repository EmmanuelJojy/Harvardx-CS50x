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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    int sepiaRed, sepiaGreen, sepiaBlue;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            //evaluvating sepia_ for all colours
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
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
