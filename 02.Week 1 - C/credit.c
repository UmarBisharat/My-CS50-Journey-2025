#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int main(void)
{
    long long number;
    printf("Number: ");
    scanf("%lld", &number);

    // Count digits and check validity
    long long temp = number;
    int digits = 0;
    while (temp > 0)
    {
        digits++;
        temp /= 10;
    }

    // Luhn's Algorithm
    long long n = number;
    int sum = 0;
    bool alternate = false;

    while (n > 0)
    {
        int digit = n % 10;

        if (alternate)
        {
            digit *= 2;
            if (digit > 9)
            {
                digit -= 9;
            }
        }

        sum += digit;
        alternate = !alternate;
        n /= 10;
    }

    // Check starting digits and length
    long long first_two = number;
    while (first_two > 99)
    {
        first_two /= 10;
    }

    long long first_four = number;
    while (first_four > 9999)
    {
        first_four /= 10;
    }

    if (sum % 10 == 0)
    {
        if ((first_two == 34 || first_two == 37) && digits == 15)
        {
            printf("AMEX\n");
        }
        else if (first_four >= 5100 && first_four <= 5500 && digits == 16)
        {
            printf("MASTERCARD\n");
        }
        else if ((first_two / 10) == 4 && (digits == 13 || digits == 16))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
