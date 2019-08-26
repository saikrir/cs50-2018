#include <stdio.h>
#include <cs50.h>
#include <math.h>

long get_credit_card_number();
int get_credit_card_number_length(long credit_card_number);
int reduce_to_sum_of_digits(int number);
bool is_last_digit_zero(int number);
bool is_checksum_valid(long credit_card_number);

int main(int argc, char const *argv[])
{
    long credit_card_number = get_credit_card_number();

    int credit_card_length = get_credit_card_number_length(credit_card_number);

    long firstTwo = credit_card_number / powl(10, credit_card_length - 2);

    char *validityMessage = is_checksum_valid(credit_card_number) ? "Valid" : "Invalid";

    if (credit_card_length == 15 && (firstTwo == 37 || firstTwo == 34))
    {
        printf("American Express is %s \n", validityMessage);
    }
    else if (credit_card_length == 16 && (firstTwo >= 51 && firstTwo <= 55))
    {
        printf("MasterCard is %s \n", validityMessage);
    }
    else if ((credit_card_length == 16 || credit_card_length == 13) && (firstTwo >= 40 && firstTwo <= 49))
    {
        printf("Visa is %s \n", validityMessage);
    }
    else
    {
        printf("Credit Card is invalid \n");
    }
    return 0;
}

long get_credit_card_number()
{
    long credit_card_number = get_long("Please enter a credit card number :");
    return credit_card_number;
}

int get_credit_card_number_length(long credit_card_number)
{
    int ctr = 0;
    for (; credit_card_number != 0; ctr++)
    {
        credit_card_number /= 10;
    }
    return ctr;
}

int reduce_to_sum_of_digits(int number)
{
    int sum = 0;
    do
    {
        sum += number % 10;
        number = number / 10;
    } while (number != 0);
    return sum;
}

bool is_last_digit_zero(int number)
{
    if (number == 0)
    {
        return true;
    }
    else
    {
        int digit = number % 10;
        return digit == 0;
    }
}

bool is_checksum_valid(long credit_card_number)

{
    int sum = 0;
    for (int i = 0; credit_card_number != 0; i++)
    {
        int digit = credit_card_number % 10;
        credit_card_number = credit_card_number / 10;
        if (i % 2 == 0)
        {
            sum += digit;
        }
        else
        {
            digit = digit * 2;
            int reducedDigit = (digit > 9) ? reduce_to_sum_of_digits(digit) : digit;
            sum += reducedDigit;
        }
    }
    return is_last_digit_zero(sum);
}
