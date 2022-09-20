#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //card no and copies for operations
    long n, copy = 0, copy1; 
    int len = 0, sum = 0, flag = 0, i;
    string type = "";
    
    //input
    do
    {
        n = get_long("Number: ");
    }
    while (n <= 0);
    copy1 = n;
    
    //reverse
    while (n != 0)
    {
        copy = (copy * 10) + (n % 10);
        n = n / 10;
        len += 1;
    }
    
    //preliminary test
    if ((copy % 100 == 43 || copy % 100 == 73) && len == 15)
    {
        type = "AMEX";
    }
    else if ((copy % 100 == 15 || copy % 100 == 25 || copy % 100 == 35 || copy % 10 == 45 || copy % 100 == 55) && len == 16)
    {
        type = "MASTERCARD";
    }
    else if (copy % 10 == 4 && (len == 13 || len == 16))
    {
        type = "VISA";
    }
    else
    {
        //Incase all test cases fail 
        flag = 1;
    }
    
    //Luhn algorithm implementation
    while (copy1 != 0)
    {
        //adding non doubled elements to sum
        sum += (copy1 % 10);
        copy1 /= 10;
        
        //doubling every other digit
        i = (copy1 % 10) * 2;
        while (i != 0)
        {
            //splitting douled elements
            sum += (i % 10);
            i /= 10;
        }
        copy1 /= 10;
    }
    
    //final check for compatibility
    if (sum % 10 == 0 && flag != 1)
    {
        printf("%s\n", type);
    }
    else
    {
        printf("INVALID\n");
    }
    
}