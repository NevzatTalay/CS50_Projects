#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int digitcheck;
int main(int argc, string argv[])
{
    //this is addded to makes sure digit check. if is there because to check argv it has to exist.
    if (argc == 2)
    {
        //is all argv elements are digit or nor.
        for (int j = 0; j < strlen(argv[1]); j++)
        {
            if (isdigit(argv[1][j]) == false)
            {
                digitcheck = 1;
            }
            else
            {
                digitcheck = 0;
            }
        }
    }
//argc =2 to take appropriate arguments 0< to be sure is integer and digit check to be sure digits only
    if (argc == 2 && 0 < atoi(argv[1]) && digitcheck == 0)
    {
        string input = get_string("plaintext: ");
//check every letter
        for (int i = 0; i < strlen(input); i++)
        {
            char letternum = input[i];
            //lower case
            if (96 < letternum && letternum < 123)
            {
                int letter = (input[i] - 'a' + atoi(argv[1])) % 26 + 97;
                input[i] = letter;
            }
            //upper case
            else if (64 < letternum && letternum < 91)
            {
                int letter = (input[i] - 'A' + atoi(argv[1])) % 26 + 65;
                input[i] = letter;
            }
            //other letters are kept same
            else
            {
                input[i] = input[i];
            }
        }
        //the result is below.
        printf("ciphertext: %s\n", input);
        return 0;
    }
    else
    {
        //returns 1 with 1 problem
        printf("Usage: ./caesar key\n");
        return 1;
    }
}