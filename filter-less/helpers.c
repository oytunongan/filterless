#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int ave = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = ave;
            image[i][j].rgbtGreen = ave;
            image[i][j].rgbtBlue = ave;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int original[3] = {image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue};
            int finalRed = round(0.393 * original[0] + 0.769 * original[1] + 0.189 * original[2]);
            int finalGreen = round(0.349 * original[0] + 0.686 * original[1] + 0.168 * original[2]);
            int finalBlue = round(0.272 * original[0] + 0.534 * original[1] + 0.131 * original[2]);
            int changed[3];
            changed[0] = finalRed;
            changed[1] = finalGreen;
            changed[2] = finalBlue;
            for (int k = 0; k < 3; k++)
            {
                if (changed[k] > 255)
                {
                    changed[k] = 255;
                }
            }
            image[i][j].rgbtRed = changed[0];
            image[i][j].rgbtGreen = changed[1];
            image[i][j].rgbtBlue = changed[2];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    uint8_t tr, tg, tb;
    for (int i = 0; i < height; i++)
    {
        int k = width - 1;
        for (int j = 0; j < width; j++)
        {
            if (j < k)
            {
                uint8_t r = image[i][j].rgbtRed;
                uint8_t g = image[i][j].rgbtGreen;
                uint8_t b = image[i][j].rgbtBlue;
                image[i][j].rgbtRed = image[i][k].rgbtRed;
                image[i][j].rgbtGreen = image[i][k].rgbtGreen;
                image[i][j].rgbtBlue = image[i][k].rgbtBlue;
                image[i][k].rgbtRed = r;
                image[i][k].rgbtGreen = g;
                image[i][k].rgbtBlue = b;
            }
            k--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            int sum1 = 0;
            int sum2 = 0;
            int sum3 = 0;
            int ave1 = 0;
            int ave2 = 0;
            int ave3 = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                if ((k >= 0) && (k < height))
                {
                    for (int l = j - 1; l <= j + 1; l++)
                    {
                        if ((l >= 0) && (l < width))
                        {
                            sum1 += image[k][l].rgbtRed;
                            sum2 += image[k][l].rgbtGreen;
                            sum3 += image[k][l].rgbtBlue;
                            count++;
                        }
                    }
                }
            }
            ave1 = round(sum1 / (float) count);
            ave2 = round(sum2 / (float) count);
            ave3 = round(sum3 / (float) count);
            copy[i][j].rgbtRed = ave1;
            copy[i][j].rgbtGreen = ave2;
            copy[i][j].rgbtBlue = ave3;
        }
    }
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            image[m][n].rgbtRed = copy[m][n].rgbtRed;
            image[m][n].rgbtGreen = copy[m][n].rgbtGreen;
            image[m][n].rgbtBlue = copy[m][n].rgbtBlue;
        }
    }
    return;
}
