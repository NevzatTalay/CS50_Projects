#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long result;
    long cardnumber, powerofnum, temp, residual, evensum;
    int i, oddevencounter;

    residual = 0;
    evensum = 0;

    // Get the card value
    cardnumber = get_long("Enter your Card Number: ");

    for (i = 1; i < 19; ++i)
    {
        powerofnum = pow(10, i);
        temp = cardnumber % powerofnum;
        result = (temp - residual) / (powerofnum / 10);
        residual = temp;
        //taking even digits lower than 5
        if (i % 2 == 0 && 2 * result < 10)
        {
            evensum = evensum + 2 * result;
        }
        //taking even digits higher than 4
        else if (i % 2 == 0 && 2 * result >= 10)
        {
            evensum = evensum + (2 * result % 10) + 1;
        }
        //taking odd digits
        else if (i % 2 == 1)
        {
            evensum = evensum + result;
        }
    }
//American Express is 15 digits and starts with 34 and 37
    if ((cardnumber >= 340000000000000 && cardnumber <= 349999999999999 && evensum % 10 == 0) || (cardnumber >= 370000000000000
            && cardnumber <= 379999999999999 && evensum % 10 == 0))
    {
        printf("AMEX\n");
    }
    //MasterCard is 16 digits and starts with 51,52,53,54,55
    else if ((cardnumber >= 5100000000000000 && cardnumber <= 5199999999999999 && evensum % 10 == 0)
             || (cardnumber >= 5200000000000000
                 && cardnumber <= 5299999999999999 && evensum % 10 == 0) || (cardnumber >= 5300000000000000 && cardnumber <= 5399999999999999
                         && evensum % 10 == 0) || (cardnumber >= 5400000000000000 && cardnumber <= 5499999999999999 && evensum % 10 == 0)
             || (cardnumber >= 5500000000000000 && cardnumber <= 5599999999999999 && evensum % 10 == 0))
    {
        printf("MASTERCARD\n");
    }
    //VISA is 13 or 16 digits and starts with 4
    else if ((cardnumber >= 4000000000000 && cardnumber <= 4999999999999 && evensum % 10 == 0) || (cardnumber >= 4000000000000000
             && cardnumber <= 4999999999999999 && evensum % 10 == 0))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
