#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // creating a variable holding name of the file
    char *filename = malloc(8);
    int pict_count = 0;
    sprintf(filename, "%03i.jpg", pict_count);

    // a file to keep imagines
    FILE *img = fopen(filename, "w");
    if (img == NULL)
    {
        printf("File doesn't exist!");
        return 1;
    }

    //reading all bites from input file

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("File doesn't exist!");
        return 1;
    }

    BYTE buffer[512];
    while (fread(buffer, sizeof(BYTE), 512, file))
    {
        // checking, if thats a start of new jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // first picture
            if (pict_count == 0)
            {
                fwrite(buffer, sizeof(BYTE), 512, img);
                pict_count += 1;
            }
            // any next picture
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", pict_count);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), 512, img);
                pict_count += 1;
            }
        }
        // writting all 512 pices of each imagine
        else
        {
            if (pict_count > 0)
            {
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
        }
    }
    fclose(img);
    free(filename);
}