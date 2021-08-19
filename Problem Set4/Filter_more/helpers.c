#include "helpers.h"
#include <math.h>

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
    image[0][0].rgbtBlue = round((copy[0][0].rgbtBlue + copy[0][1].rgbtBlue +
                                  copy[1][0].rgbtBlue + copy[1][1].rgbtBlue) / 4.0);
    image[0][0].rgbtGreen = round((copy[0][0].rgbtGreen + copy[0][1].rgbtGreen +
                                   copy[1][0].rgbtGreen + copy[1][1].rgbtGreen) / 4.0);
    image[0][0].rgbtRed = round((copy[0][0].rgbtRed + copy[0][1].rgbtRed +
                                 copy[1][0].rgbtRed + copy[1][1].rgbtRed) / 4.0);
    //corner left bottom
    image[height - 1][0].rgbtBlue = round((copy[height - 1][0].rgbtBlue +
                                           copy[height - 2][0].rgbtBlue + copy[height - 2][1].rgbtBlue + copy[height - 1][1].rgbtBlue) / 4.0);
    image[height - 1][0].rgbtGreen = round((copy[height - 1][0].rgbtGreen +
                                            copy[height - 2][0].rgbtGreen + copy[height - 2][1].rgbtGreen + copy[height - 1][1].rgbtGreen) / 4.0);
    image[height - 1][0].rgbtRed = round((copy[height - 1][0].rgbtRed +
                                          copy[height - 2][0].rgbtRed + copy[height - 2][1].rgbtRed + copy[height - 1][1].rgbtRed) / 4.0);
    //corner right top
    image[0][width - 1].rgbtBlue = round((copy[0][width - 1].rgbtBlue + copy[0][width - 2].rgbtBlue +
                                          copy[1][width - 1].rgbtBlue + copy[1][width - 2].rgbtBlue) / 4.0);
    image[0][width - 1].rgbtGreen = round((copy[0][width - 1].rgbtGreen + copy[0][width - 2].rgbtGreen +
                                           copy[1][width - 1].rgbtGreen + copy[1][width - 2].rgbtGreen) / 4.0);
    image[0][width - 1].rgbtRed = round((copy[0][width - 1].rgbtRed + copy[0][width - 2].rgbtRed +
                                         copy[1][width - 1].rgbtRed + copy[1][width - 2].rgbtRed) / 4.0);
    //corner right bottom
    image[height - 1][width - 1].rgbtBlue = round((copy[height - 1][width - 1].rgbtBlue +
                                            copy[height - 2][width - 1].rgbtBlue + copy[height - 2][width - 2].rgbtBlue + copy[height - 1][width - 2].rgbtBlue) / 4.0);
    image[height - 1][width - 1].rgbtGreen = round((copy[height - 1][width - 1].rgbtGreen +
            copy[height - 2][width - 1].rgbtGreen + copy[height - 2][width - 2].rgbtGreen + copy[height - 1][width - 2].rgbtGreen) / 4.0);
    image[height - 1][width - 1].rgbtRed = round((copy[height - 1][width - 1].rgbtRed +
                                           copy[height - 2][width - 1].rgbtRed + copy[height - 2][width - 2].rgbtRed + copy[height - 1][width - 2].rgbtRed) / 4.0);

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //copy of oryginal image
    RGBTRIPLE copy [height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy [i][j] = image [i][j];
        }
    }

    // middle & edges
    int Gxmat[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gymat[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            int GxBlue = 0;
            int GxRed = 0;
            int GxGreen = 0;
            int GyBlue = 0;
            int GyRed = 0;
            int GyGreen = 0;

            // middle
            if (i > 0 && i < (height - 1) && j > 0 && j < (width - 1))
            {
                int c = -1;
                for (int k = i - 1; k < (i + 2); k++)
                {
                    c = c + 1;
                    int v = -1;
                    for (int l = j - 1; l < (j + 2); l++)
                    {
                        v = v + 1;
                        GxBlue += copy[k][l].rgbtBlue * Gxmat[c][v];
                        GxRed += copy[k][l].rgbtRed * Gxmat[c][v];
                        GxGreen += copy[k][l].rgbtGreen * Gxmat[c][v];
                        GyBlue += copy[k][l].rgbtBlue * Gymat[c][v];
                        GyRed += copy[k][l].rgbtRed * Gymat[c][v];
                        GyGreen +=  copy[k][l].rgbtGreen * Gymat[c][v];
                    }

                }
            }
            //top edge
            else if (i == 0 && j > 0 && j < (width - 1))
            {
                int c = 0;

                for (int k = i; k < i + 2; k++)
                {
                    c = c + 1;
                    int v = -1;
                    for (int l = j - 1; l < j + 2; l++)
                    {
                        v = v + 1;
                        GxBlue = GxBlue + copy[k][l].rgbtBlue * Gxmat[c][v];
                        GxRed = GxRed + copy[k][l].rgbtRed * Gxmat[c][v];
                        GxGreen = GxGreen + copy[k][l].rgbtGreen * Gxmat[c][v];
                        GyBlue = GyBlue + copy[k][l].rgbtBlue * Gymat[c][v];
                        GyRed = GyRed + copy[k][l].rgbtRed * Gymat[c][v];
                        GyGreen = GyGreen + copy[k][l].rgbtGreen * Gymat[c][v];
                    }

                }
            }
            //bottom edge
            else if (i == (height - 1) && j > 0 && j < (width - 1))
            {
                int c = -1;

                for (int k = i - 1; k < i + 1; k++)
                {
                    c = c + 1;
                    int v = -1;
                    for (int l = j - 1; l < j + 2; l++)
                    {
                        v = v + 1;
                        GxBlue = GxBlue + copy[k][l].rgbtBlue * Gxmat[c][v];
                        GxRed = GxRed + copy[k][l].rgbtRed * Gxmat[c][v];
                        GxGreen = GxGreen + copy[k][l].rgbtGreen * Gxmat[c][v];
                        GyBlue = GyBlue + copy[k][l].rgbtBlue * Gymat[c][v];
                        GyRed = GyRed + copy[k][l].rgbtRed * Gymat[c][v];
                        GyGreen = GyGreen + copy[k][l].rgbtGreen * Gymat[c][v];
                    }

                }

            }
            //left edge
            else if (i > 0 && i < (height - 1) && j == 0)
            {
                int c = -1;

                for (int k = i - 1; k < i + 2; k++)
                {
                    c = c + 1;
                    int v = 0;
                    for (int l = j; l < j + 2; l++)
                    {
                        v = v + 1;
                        GxBlue = GxBlue + copy[k][l].rgbtBlue * Gxmat[c][v];
                        GxRed = GxRed + copy[k][l].rgbtRed * Gxmat[c][v];
                        GxGreen = GxGreen + copy[k][l].rgbtGreen * Gxmat[c][v];
                        GyBlue = GyBlue + copy[k][l].rgbtBlue * Gymat[c][v];
                        GyRed = GyRed + copy[k][l].rgbtRed * Gymat[c][v];
                        GyGreen = GyGreen + copy[k][l].rgbtGreen * Gymat[c][v];
                    }

                }

            }
            //right edge
            else if (i > 0 && i < (height - 1) && j == (width - 1))
            {
                int c = -1;

                for (int k = i - 1; k < i + 2; k++)
                {
                    c = c + 1;
                    int v = -1;
                    for (int l = j - 1; l < j + 1; l++)
                    {
                        v = v + 1;
                        GxBlue = GxBlue + copy[k][l].rgbtBlue * Gxmat[c][v];
                        GxRed = GxRed + copy[k][l].rgbtRed * Gxmat[c][v];
                        GxGreen = GxGreen + copy[k][l].rgbtGreen * Gxmat[c][v];
                        GyBlue = GyBlue + copy[k][l].rgbtBlue * Gymat[c][v];
                        GyRed = GyRed + copy[k][l].rgbtRed * Gymat[c][v];
                        GyGreen = GyGreen + copy[k][l].rgbtGreen * Gymat[c][v];
                    }

                }

            }
            int valueBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
            int valueRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
            int valueGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));

            if (valueBlue <= 255)
            {
                image[i][j].rgbtBlue = valueBlue;
            }

            else if (valueBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }


            if (valueRed <= 255)
            {
                image[i][j].rgbtRed = valueRed;
            }

            else if (valueRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }


            if (valueGreen <= 255)
            {
                image[i][j].rgbtGreen = valueGreen;
            }

            else if (valueGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }


        }
    }

    // corner left top
    int valueBlueLT = round(sqrt(pow((copy[0][1].rgbtBlue * 2 + copy[1][1].rgbtBlue), 2) +
                                 (pow((copy[1][1].rgbtBlue + copy[1][0].rgbtBlue * 2), 2))));
    int valueRedLT = round(sqrt(pow((copy[0][1].rgbtRed * 2 + copy[1][1].rgbtRed), 2) +
                                (pow((copy[1][1].rgbtRed + copy[1][0].rgbtRed * 2), 2))));
    int valueGreenLT = round(sqrt(pow((copy[0][1].rgbtGreen * 2 + copy[1][1].rgbtGreen), 2) +
                                  (pow((copy[1][1].rgbtGreen + copy[1][0].rgbtGreen * 2), 2))));

    if (valueBlueLT < 255)
    {
        image[0][0].rgbtBlue = valueBlueLT;
    }

    else if (valueBlueLT >= 255)
    {
        image[0][0].rgbtBlue = 255;
    }


    if (valueRedLT < 255)
    {
        image[0][0].rgbtRed = valueRedLT;
    }

    else if (valueRedLT >= 255)
    {
        image[0][0].rgbtRed = 255;
    }


    if (valueGreenLT < 255)
    {
        image[0][0].rgbtGreen = valueGreenLT;
    }

    else if (valueGreenLT >= 255)
    {
        image[0][0].rgbtBlue = 255;
    }




    //corner left bottom
    int valueBlueLB = round(sqrt(pow((copy[height - 1][1].rgbtBlue * 2 +
                                      copy[height - 2][1].rgbtBlue), 2) + (pow((copy[height - 2][0].rgbtBlue * (- 2) -
                                              copy[height - 2][1].rgbtBlue), 2))));
    int valueRedLB = round(sqrt(pow((copy[height - 1][1].rgbtRed * 2 +
                                     copy[height - 2][1].rgbtRed), 2) + (pow((copy[height - 2][0].rgbtRed * (- 2) -
                                             copy[height - 2][1].rgbtRed), 2))));
    int valueGreenLB = round(sqrt(pow((copy[height - 1][1].rgbtGreen * 2 +
                                       copy[height - 2][1].rgbtGreen), 2) + (pow((copy[height - 2][0].rgbtGreen * (- 2) -
                                               copy[height - 2][1].rgbtGreen), 2))));

    if (valueBlueLB < 255)
    {
        image[height - 1][0].rgbtBlue = valueBlueLB;
    }

    else if (valueBlueLB >= 255)
    {
        image[height - 1][0].rgbtBlue = 255;
    }


    if (valueRedLB < 255)
    {
        image[height - 1][0].rgbtRed = valueRedLB;
    }

    else if (valueRedLB >= 255)
    {
        image[height - 1][0].rgbtRed = 255;
    }


    if (valueGreenLB < 255)
    {
        image[height - 1][0].rgbtGreen = valueGreenLB;
    }

    else if (valueGreenLB >= 255)
    {
        image[height - 1][0].rgbtBlue = 255;
    }


    //corner right top
    int valueBlueRT = round(sqrt(pow((copy[0][width - 2].rgbtBlue * (- 2) -
                                      copy[1][width - 2].rgbtBlue), 2) + (pow((copy[1][width - 1].rgbtBlue *  2 +
                                              copy[1][width - 2].rgbtBlue), 2))));
    int valueRedRT = round(sqrt(pow((copy[0][width - 2].rgbtRed * (- 2) -
                                     copy[1][width - 2].rgbtRed), 2) + (pow((copy[1][width - 1].rgbtRed *  2 +
                                             copy[1][width - 2].rgbtRed), 2))));
    int valueGreenRT = round(sqrt(pow((copy[0][width - 2].rgbtGreen * (- 2) -
                                       copy[1][width - 2].rgbtGreen), 2) + (pow((copy[1][width - 1].rgbtGreen *  2 +
                                               copy[1][width - 2].rgbtGreen), 2))));

    if (valueBlueRT < 255)
    {
        image[0][width - 1].rgbtBlue = valueBlueRT;
    }

    else if (valueBlueRT >= 255)
    {
        image[0][width - 1].rgbtBlue = 255;
    }


    if (valueRedRT < 255)
    {
        image[0][width - 1].rgbtRed = valueRedRT;
    }

    else if (valueRedRT >= 255)
    {
        image[0][width - 1].rgbtRed = 255;
    }


    if (valueGreenRT < 255)
    {
        image[0][width - 1].rgbtGreen = valueGreenRT;
    }

    else if (valueGreenRT >= 255)
    {
        image[0][width - 1].rgbtGreen = 255;
    }

    //corner right bottom

    int valueBlueRB = round(sqrt(pow((copy[height - 1][width - 2].rgbtBlue * (- 2) -
                                      copy[height - 2][width - 2].rgbtBlue), 2) + (pow((copy[height - 2][width - 1].rgbtBlue * (- 2) -
                                              copy[height - 2][width - 2].rgbtBlue), 2))));
    int valueRedRB = round(sqrt(pow((copy[height - 1][width - 2].rgbtRed * (- 2) -
                                     copy[height - 2][width - 2].rgbtRed), 2) + (pow((copy[height - 2][width - 1].rgbtRed * (- 2) -
                                             copy[height - 2][width - 2].rgbtRed), 2))));
    int valueGreenRB = round(sqrt(pow((copy[height - 1][width - 2].rgbtGreen * (- 2) -
                                       copy[height - 2][width - 2].rgbtGreen), 2) + (pow((copy[height - 2][width - 1].rgbtGreen * (- 2) -
                                               copy[height - 2][width - 2].rgbtGreen), 2))));

    if (valueBlueRB < 255)
    {
        image[height - 1][width - 1].rgbtBlue = valueBlueRB;
    }

    else if (valueBlueRB >= 255)
    {
        image[height - 1][width - 1].rgbtBlue = 255;
    }


    if (valueRedRB < 255)
    {
        image[height - 1][width - 1].rgbtRed = valueRedRB;
    }

    else if (valueRedRB >= 255)
    {
        image[height - 1][width - 1].rgbtRed = 255;
    }


    if (valueGreenRB < 255)
    {
        image[height - 1][width - 1].rgbtGreen = valueGreenRB;
    }

    else if (valueGreenRB >= 255)
    {
        image[height - 1][width - 1].rgbtBlue = 255;
    }

    return;
}
