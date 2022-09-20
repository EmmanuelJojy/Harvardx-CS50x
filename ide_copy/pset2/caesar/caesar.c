#include <cs50.h>
#include <string.h>
//atoi for string -> int
#include <stdlib.h>
#include <stdio.h>

//checks if command line argument is valid
bool valid(int argc, string argv[]);

//prints encrypted cipher text
void encrypt(string s, int key);

//shift character based on key
char shift(char c, int d, int key);

int main(int argc, string argv[])
{
    //checking command line arg
    if (! valid(argc, argv))
    {
        printf("Usage: ./caesar key\n");
        return (1);
    }
    
    //converting string key -> int key
    int key = atoi(argv[1]);
    //prompt for plaintext
    string s = get_string("plaintext: ");
    printf("ciphertext: ");
    //call to encrypt function
    encrypt(s, key);
    printf("\n");
    return (0);
}

bool valid(int argc, string argv[])
{
    //check no. of args
    if (argc != 2)
    {
        return (false);
    }
    //checks if key is number
    for (int i = 0, l = strlen(argv[1]); i < l; i ++)
    {
        if (argv[1][i] >= '1' && argv[1][i] <= '9')
        {
            continue;
        }
        return (false);
    }
    //returns true if both conditions validate
    return (true);
}

void encrypt(string s, int key)
{
    for (int i = 0, l = strlen(s); i < l; i ++)
    {
        //if character is uppercase...
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            printf("%c", shift(s[i], 64, key));
        }
        //if cahracter is lowercase...
        else if (s[i] >= 'a' && s[i] <= 'z')
        {
            printf("%c", shift(s[i], 96, key));
        }
        //if character is non - alphabet
        else
        {
            printf("%c", s[i]);
        }
    }
}

char shift(char c, int d, int key)
{
    //shift formula based on ASCII
    int i = c - d + key;
    return (char)((i % 26) + d);
    
}