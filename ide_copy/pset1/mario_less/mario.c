#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    //Accepting integer input between 1 and 8
    //include 1 and 8
    do
    {
        //integr input function from cs50
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8); 
    //generating pattern
    for (int i = 0; i < n; i++)
    {
        //printing space
        for (int j = 0; j < n - i - 1; j++)
        {
            printf(" ");
        }
        //printing # 
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        //goto new line after # is printed
        printf("\n");
    }
}