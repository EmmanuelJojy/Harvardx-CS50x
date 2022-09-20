#include <cs50.h>
#include <stdio.h>
//math header file for round function
#include <math.h>

int main(void)
{
    //dollars: accept the input in dollars
    //cents: to convert dollars to cents
    //n: temporary variable to store coins
    //coin: no of coins
    float dollars;
    int cents, n, coin = 0;
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars <= 0.0);
    cents = round(dollars * 100);
    if (cents / 25 >= 1)
    {
        n = cents / 25;
        coin += n;
        cents -= (n * 25);
    }
    if (cents / 10 >= 1)
    {
        n = cents / 10;
        coin += n;
        cents -= (n * 10);
    }
    if (cents / 5 >= 1.0)
    {
        n = cents / 5;
        coin += n;
        cents -= (n * 5);
    }
    coin += cents;
    printf("%d\n", coin);
}