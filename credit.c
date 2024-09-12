// This program tests card numbers from multiple card companies to see if they are valid

#include <cs50.h>
#include <math.h>
#include <stdio.h>

int checksum(long cc);

int length(long card);

int main(void)
{
    // Prompts the user to enter a card number
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 0);

    // Validates the checksum of the card number
    int validate = checksum(number);

    // If checksum ends in zero checks length and starting values to determine card type
    if (validate == 0)
    {
        int company = length(number);

        // Prints company based on the value of length function
        if (company == 1)
        {
            printf("AMEX\n");
        }
        else if (company == 2)
        {
            printf("MASTERCARD\n");
        }
        else if (company == 3)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // If checksum does not end in zero prints invalid
    else
    {
        printf("INVALID\n");
    }
}

int checksum(long cc)
{
    // Initialization
    int sum1 = 0;
    int sum2 = 0;
    int mod = 0;
    int multiply = 0;
    int validate = 0;

    // Calculates checksum
    while (cc > 0)
    {
        // Retrieve last digit
        mod = cc % 10;
        // Add to sum 2
        sum2 = sum2 + mod;
        // Move one digit over
        cc = cc / 10;
        // Retrieve digit
        mod = cc % 10;
        // Mutiply digit by 2
        multiply = mod * 2;
        // Adds digits of multiplied number
        if (multiply > 9)
        {
            multiply = multiply % 10;
            // Highest number a single digit x 2 is 18 thus left digit is always 1
            sum1 = sum1 + multiply + 1;
        }
        else
        {
            multiply = multiply % 10;
            sum1 = sum1 + multiply;
        }
        // Move one digit over
        cc = cc / 10;
    }
    // Calculates final checksum
    validate = sum1 + sum2;
    validate = validate % 10;
    return validate;
}

int length(long card)
{
    // Initialization
    int digits = 0;
    int mod1 = 0;
    int mod2 = 0;
    int company = 0;

    // Checks the card length storing it in the variable digits and saves first two digits of card
    while (card > 0)
    {
        // Move one digit over when greater than 99
        if (card > 99)
        {
            card = card / 10;
            digits = digits + 1;
        }
        // Moves one digit over and stores digit in mod1 when greater than 9
        else if (card > 9)
        {
            mod1 = card % 10;
            card = card / 10;
            digits = digits + 1;
        }
        // Moves one digit over and stores digit in mod2
        else
        {
            mod2 = card % 10;
            card = card / 10;
            digits = digits + 1;
        }
    }

    // Prints the card company or invalid
    if (digits == 15 && mod2 == 3 && (mod1 == 4 || mod1 == 7))
    {
        // AMEX
        company = 1;
    }
    else if (digits == 16 && mod2 == 5 &&
             (mod1 == 1 || mod1 == 2 || mod1 == 3 || mod1 == 4 || mod1 == 5))
    {
        // MASTERCARD
        company = 2;
    }
    else if ((digits == 13 || digits == 16) && mod2 == 4)
    {
        // VISA
        company = 3;
    }
    else
    {
        // INVALID
        company = 0;
    }
    return company;
}
