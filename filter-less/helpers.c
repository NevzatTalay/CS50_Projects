#include "helpers.h"
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j].rgbtBlue + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][j].rgbtRed;
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
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
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
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempnumbers[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempnumbers[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            tempnumbers[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            tempnumbers[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtGreen = tempnumbers[i][j].rgbtGreen;
            image[i][j].rgbtRed = tempnumbers[i][j].rgbtRed;
            image[i][j].rgbtBlue = tempnumbers[i][j].rgbtBlue;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create temporary variable to prevent blur operation interfere with eachother.
    RGBTRIPLE tempnumbers[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //top left corner
            if (i == 0 && j == 0)
            {
                //green
                tempnumbers[i][j].rgbtGreen =
                    round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 4.0);
                //red
                tempnumbers[i][j].rgbtRed
                    = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 4.0);
                //blue
                tempnumbers[i][j].rgbtBlue
                    = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 4.0);
            }
            //top right corner
            else if (i == 0 && j == width - 1)
            {
                //green
                tempnumbers[i][j].rgbtGreen
                    = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 4.0);
                //red
                tempnumbers[i][j].rgbtRed
                    = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 4.0);
                //blue
                tempnumbers[i][j].rgbtBlue
                    = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 4.0);
            }
            //left bottom corner
            else if (i == height - 1 && j == 0)
            {
                //green
                tempnumbers[i][j].rgbtGreen
                    = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 4.0);
                //red
                tempnumbers[i][j].rgbtRed
                    = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 4.0);
                //blue
                tempnumbers[i][j].rgbtBlue
                    = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 4.0);
            }
            //right bottom corner
            else if (i == height - 1 && j == width - 1)
            {
                //green
                tempnumbers[i][j].rgbtGreen
                    = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 4.0);
                //red
                tempnumbers[i][j].rgbtRed
                    = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed) / 4.0);
                //blue
                tempnumbers[i][j].rgbtBlue
                    = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 4.0);
            }
            //top horizontal blocks
            else if (i == 0)
            {
                //green
                tempnumbers[i][j].rgbtGreen
                    = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                             image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0);
                //red
                tempnumbers[i][j].rgbtRed
                    = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                             image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0);
                //blue
                tempnumbers[i][j].rgbtBlue
                    = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                             image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0);
            }
            //right vertical blocks
            else if (j == width - 1)
            {
                //green
                tempnumbers[i][j].rgbtGreen
                    = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen
                             + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6.0);
                //red
                tempnumbers[i][j].rgbtRed
                    = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed
                             + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6.0);
                //blue
                tempnumbers[i][j].rgbtBlue
                    = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue
                             + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6.0);
            }
            //bottom horizontal blocks
            else if (i == height - 1)
            {
                //green
                tempnumbers[i][j].rgbtGreen
                    = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen
                             + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6.0);
                //red
                tempnumbers[i][j].rgbtRed
                    = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed
                             + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6.0);
                //blue
                tempnumbers[i][j].rgbtBlue
                    = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue
                             + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6.0);
            }
            //left vertical blocks
            else if (j == 0)
            {
                //green
                tempnumbers[i][j].rgbtGreen
                    = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen
                             + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0);
                //red
                tempnumbers[i][j].rgbtRed
                    = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed
                             + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0);
                //blue
                tempnumbers[i][j].rgbtBlue
                    = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue
                             + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0);
            }
            //middle blocks
            else
            {
                //green
                tempnumbers[i][j].rgbtGreen
                    = round((image[i][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen
                             + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen
                             + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9.0);
                //red
                tempnumbers[i][j].rgbtRed
                    = round((image[i][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed
                             + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j + 1].rgbtRed
                             + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9.0);
                //blue
                tempnumbers[i][j].rgbtBlue
                    = round((image[i][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue
                             + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue
                             + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9.0);
            }
        }
    }
    //create the final image from the temporary array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtGreen = tempnumbers[i][j].rgbtGreen;
            image[i][j].rgbtRed = tempnumbers[i][j].rgbtRed;
            image[i][j].rgbtBlue = tempnumbers[i][j].rgbtBlue;
        }
    }

    return;
}
