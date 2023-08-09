#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    FILE *file = NULL;
    FILE *img = NULL;
    BYTE arr[512];
    char filename[8];
    int counter = 0;
    // This part is to check whether command is inserted with an argument(file name)
    if (argv[1] != NULL)
    {
        file = fopen(argv[1], "r");
    }
    else
    {
        printf("Enter a valid file name\n");
        return 1;
    }
    // This while runs on every 512 byte chunk of raw file.
    while (fread(arr, 1, 512, file) == 512)
    {
        // if is used here to find the beginning of jpeg file. if 4 conditions are met most likely you have found a corrupted jpeg file.
        if (arr[0] == 0xff && arr[1] == 0xd8 && arr[2] == 0xff && (arr[3] & 0xf0) == 0xe0)
        {
            // I add this condition to find the end of jpg file, because I increase the counter value by one if I found a jpg everytime
            if (!(counter == 0))
            {
                fclose(img);
            }
            // this is the place of creation. JPeg files are created here.
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            // fwrite(arr, 1, 512, img);
            counter++;
        }
        // if counter not equal to 0, it means that we have found a jpg and it is time to write data to previously declared file.
        if (!(counter == 0))
        {
            fwrite(arr, 1, 512, img);
        }
    }
    fclose(img);
    fclose(file);
    return 0;
}