#include <cs50.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    //l, w, sen are counter variables to keep track of quantities
    //i is a temporary variable
    //len stores length of the string
    int i, len, l = 0, w = 0, sen = 0;
    //sum store the index
    float sum = 0.0;
    //s stores the letter itself
    string s = get_string("Text: ");
    //iterating over each character in string
    for (i = 0, len = strlen(s); i < len; i++)
    {
        if (s[i] == ' ')
        {
            //increments w by 1 if character is ' '
            w ++;
        }
        else if (s[i] == '.' || s[i] == '?' || s[i] == '!')
        {
            //increments sen by one if '.', '?', '!' is encountered
            sen ++;
        }
        else if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
        {
            //Incase if letter is detected
            l ++;
        }
        else
        {
            //simply goes to the next iteration in case no conditions satisfy
            continue;
        }
    }
    //incrementing w to accomodate last word
    w ++;
    //calculating Coleman-Liau index
    //index = 0.0588 * L - 0.296 * S - 15.8
    sum += 0.0588 * ((float) l / (float) w) * 100;
    sum -= 0.296 * ((float) sen / (float) w) * 100;
    sum -= 15.8;
    //rounding index to nearest whole number
    i = (int) round((sum));
    if (i < 1)
    {
        //index < 1
        printf("Before Grade 1");
    }
    else if (i >= 16)
    {
        //index [1, 16]
        printf("Grade 16+");
    }
    else
    {
        //index > 16
        printf("Grade %d", i);
    }
    //last print new line
    printf("\n");
}