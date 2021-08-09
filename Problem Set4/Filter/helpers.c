#include "helpers.h"

void swap(RGBTRIPLE *a, RGBTRIPLE *b);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
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
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;
            int red2 = round(.393 * red + .769 * green + .189 * blue);
            int green2 = round(.349 * red + .686 * green + .168 * blue);
            int blue2 = round(.272 * red + .534 * green + .131 * blue);
            if (red2 > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = red2;
            }
            if (green2 > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = green2;
            }
            if (blue2 > 255)
            {
                image[i][j].rgbtBlue = 255;
            }

            else
            {
                image[i][j].rgbtBlue = blue2;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j], &image[i][width - 1 - j]);
        }
    }
    return;
}
void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE tmp = *a;
    *a = *b;
    *b = tmp;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy [height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy [i][j] = image [i][j];
        }
    }

    //corner left top
    image[0][0].rgbtBlue = round((copy[0][0].rgbtBlue + copy[0][1].rgbtBlue + copy[1][0].rgbtBlue + copy[1][1].rgbtBlue) / 4.0);
    image[0][0].rgbtGreen = round((copy[0][0].rgbtGreen + copy[0][1].rgbtGreen + copy[1][0].rgbtGreen + copy[1][1].rgbtGreen) / 4.0);
    image[0][0].rgbtRed = round((copy[0][0].rgbtRed + copy[0][1].rgbtRed + copy[1][0].rgbtRed + copy[1][1].rgbtRed) / 4.0);
    //corner left bottom
    image[height - 1][0].rgbtBlue = round((copy[height - 1][0].rgbtBlue + copy[height - 2][0].rgbtBlue + copy[height - 2][1].rgbtBlue + copy[height - 1][1].rgbtBlue) / 4.0);
    image[height - 1][0].rgbtGreen = round((copy[height - 1][0].rgbtGreen + copy[height - 2][0].rgbtGreen + copy[height - 2][1].rgbtGreen + copy[height - 1][1].rgbtGreen) / 4.0);
    image[height - 1][0].rgbtRed = round((copy[height - 1][0].rgbtRed + copy[height - 2][0].rgbtRed + copy[height - 2][1].rgbtRed + copy[height - 1][1].rgbtRed) / 4.0);
    //corner right top
    image[0][width - 1].rgbtBlue = round((copy[0][width - 1].rgbtBlue + copy[0][width - 2].rgbtBlue + copy[1][width - 1].rgbtBlue + copy[1][width - 2].rgbtBlue) / 4.0);
    image[0][width - 1].rgbtGreen = round((copy[0][width - 1].rgbtGreen + copy[0][width - 2].rgbtGreen + copy[1][width - 1].rgbtGreen + copy[1][width - 2].rgbtGreen) / 4.0);
    image[0][width - 1].rgbtRed = round((copy[0][width - 1].rgbtRed + copy[0][width - 2].rgbtRed + copy[1][width - 1].rgbtRed + copy[1][width - 2].rgbtRed) / 4.0);
    //corner right bottom
    image[height - 1][width - 1].rgbtBlue = round((copy[height - 1][width - 1].rgbtBlue + copy[height - 2][width - 1].rgbtBlue + copy[height - 2][width - 2].rgbtBlue + copy[height - 1][width - 2].rgbtBlue) / 4.0);
    image[height - 1][width - 1].rgbtGreen = round((copy[height - 1][width - 1].rgbtGreen + copy[height - 2][width - 1].rgbtGreen + copy[height - 2][width - 2].rgbtGreen + copy[height - 1][width - 2].rgbtGreen) / 4.0);
    image[height - 1][width - 1].rgbtRed = round((copy[height - 1][width - 1].rgbtRed + copy[height - 2][width - 1].rgbtRed + copy[height - 2][width - 2].rgbtRed + copy[height - 1][width - 2].rgbtRed) / 4.0);

    //middle
    for (int i = 1; i < height - 1; i++)
    {

        for (int j = 1; j < width - 1; j++)
        {
            int sumaBlue = 0;
            int sumaRed = 0;
            int sumaGreen = 0;
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    sumaBlue = sumaBlue + copy[k][l].rgbtBlue;
                    sumaRed = sumaRed + copy[k][l].rgbtRed;
                    sumaGreen = sumaGreen + copy[k][l].rgbtGreen;
                }

            }

            image[i][j].rgbtBlue = round(sumaBlue / 9.0);
            image[i][j].rgbtRed = round(sumaRed / 9.0);
            image[i][j].rgbtGreen = round(sumaGreen / 9.0);
        }


    }
    // edge


    for (int z = 1; z < width - 1; z++)
    {
        int sumaBlue1 = 0;
        int sumaRed1 = 0;
        int sumaGreen1 = 0;
        int sumaBlue2 = 0;
        int sumaRed2 = 0;
        int sumaGreen2 = 0;

        for (int x = 0; x < 2; x++)
        {
            for (int r = z - 1; r < z + 2; r++)
            {
                sumaBlue1 = sumaBlue1 + copy[x][r].rgbtBlue;
                sumaRed1 = sumaRed1 + copy[x][r].rgbtRed;
                sumaGreen1 = sumaGreen1 + copy[x][r].rgbtGreen;

                sumaBlue2 = sumaBlue2 + copy[height - 1 - x][r].rgbtBlue;
                sumaRed2 = sumaRed2 + copy[height - 1 - x][r].rgbtRed;
                sumaGreen2 = sumaGreen2 + copy[height - 1 - x][r].rgbtGreen;
            }
        }

        image[0][z].rgbtBlue = round(sumaBlue1 / 6.0);
        image[0][z].rgbtRed = round(sumaRed1 / 6.0);
        image[0][z].rgbtGreen = round(sumaGreen1 / 6.0);
        image[height - 1][z].rgbtBlue = round(sumaBlue2 / 6.0);
        image[height - 1][z].rgbtRed = round(sumaRed2 / 6.0);
        image[height - 1][z].rgbtGreen = round(sumaGreen2 / 6.0);

    }

    for (int y = 1; y < height - 1; y++)
    {
        int sumaBlue3 = 0;
        int sumaRed3 = 0;
        int sumaGreen3 = 0;
        int sumaBlue4 = 0;
        int sumaRed4 = 0;
        int sumaGreen4 = 0;
        for (int q = 0; q < 2; q++)
        {
            for (int s = y - 1; s < y + 2; s++)
            {
                sumaBlue3 = sumaBlue3 + copy[s][q].rgbtBlue;
                sumaRed3 = sumaRed3 + copy[s][q].rgbtRed;
                sumaGreen3 = sumaGreen3 + copy[s][q].rgbtGreen;
                sumaBlue4 = sumaBlue4 + copy[s][width - 1 - q].rgbtBlue;
                sumaRed4 = sumaRed4 + copy[s][width - 1 - q].rgbtRed;
                sumaGreen4 = sumaGreen4 + copy[s][width - 1 - q].rgbtGreen;
            }
        }

        image[y][0].rgbtBlue = round(sumaBlue3 / 6.0);
        image[y][0].rgbtRed = round(sumaRed3 / 6.0);
        image[y][0].rgbtGreen = round(sumaGreen3 / 6.0);
        image[y][width - 1].rgbtBlue = round(sumaBlue4 / 6.0);
        image[y][width - 1].rgbtRed = round(sumaRed4 / 6.0);
        image[y][width - 1].rgbtGreen = round(sumaGreen4 / 6.0);
    }

    return;
}

