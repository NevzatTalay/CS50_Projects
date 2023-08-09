#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    do
    {
        //Get the height value
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int i = 0; i < height; i++)
    {
        for (int j = height; j > i + 1; j--) //to insert decreasing amount of spaces. Also inserted +1 to reach zero spaces.
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        //to create new line at the end of each loop
        printf("\n");
    }




}
