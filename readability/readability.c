#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
double numberofletters = 0;
double numberofwords = 0;
double numberofsentences = 0;
double count_letters(string text);
double count_words(string text);
double count_sentences(string text);
//<>
int main(void)
{
    string mytext = get_string("Text: ");
    //functions are run here.
    numberofletters = count_letters(mytext);
    numberofwords = count_words(mytext);
    numberofsentences = count_sentences(mytext);
    // this is for the easer of reading. I assigned them to additional variable.
    double L = 100 * (numberofletters / numberofwords);
    double S = 100 * (numberofsentences / numberofwords);
    // this is the formula to find the grade lebel
    double index = 0.0588 * L - 0.296 * S - 15.8;
    if (round(index) < 1)
    {
        //it says that it is for lowest grade.
        printf("Before Grade 1\n");
    }
    else if (round(index) > 16)
    {
        //it says that it is above highschool level.
        printf("Grade 16+\n");
    }
    else
    {
        // the extra variable added to remove zeros after dot (to make it integer)
        int result = round(index);
        printf("Grade %i\n", result);
    }
}

double count_letters(string text)
{
    // this function counts the letter by checking their ASCII numbers. They can either be lower case letter of upper case letters.
    int i;
    double lettercount = 0;
    for (i = 0; i < strlen(text); i++)
    {
        if ((text[i] <= 90 && 65 <= text[i]) || (text[i] <= 122 && 97 <= text[i]))
        {
            lettercount += 1;
        }
    }
    return lettercount;
}

double count_words(string text)
{
//This function counts the words by find the the total number of spaces. It add to one to find the real number of words.
    int i;
    double wordcount = 0;
    for (i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            wordcount += 1;
        }
    }
    return wordcount + 1;
}

double count_sentences(string text)
{
    // this function counts the sentences by checking their endings. dots exclamation marks and questions marks can only be used at the end of sentences in this app.
    int i;
    double sentencecount = 0;
    for (i = 0; i < strlen(text); i++)
    {
        if ((text[i] == '.') || (text[i] == '?') || (text[i] == '!'))
        {
            sentencecount += 1;
        }
    }
    return sentencecount;
}