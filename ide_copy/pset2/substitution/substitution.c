#include <cs50.h>
#include <string.h>
//atoi for string -> int
#include <stdlib.h>
//implement toupper()
#include <ctype.h>
#include <stdio.h>

//checks if command line argument is valid
bool valid(int argc, string argv[]);

//prints encrypted cipher text
void encrypt(string s, string key);

//shift character based on key
char shift(char c, int d, string key);

int main(int argc, string argv[])
{
    //checking command line arg
    if (! valid(argc, argv))
    {
        printf("Usage: ./caesar key\n");
        return (1);
    }

    //converting string key -> int key
    string key = argv[1];
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
    //checks if key is 26 characters long
    if (strlen(argv[1]) != 26)
    {
        return (false);
    }
    string temp[26];
    //checks if key is alphabet
    for (int i = 0, l = strlen(argv[1]); i < l; i ++)
    {
        if ((argv[1][i] >= 'A' && argv[1][i] <= 'Z') || (argv[1][i] >= 'a' && argv[1][i] <= 'z'))
        {
            //loop to check for duplicates
            for (int j = 0, count = 0; j < l; j ++)
            {
                if (toupper(argv[1][i]) == toupper(argv[1][j]))
                {
                    count ++;
                }
                if (count == 2)
                {
                    return (false);
                }
            }
            continue;
        }
        return (false);
    }
    //returns true if both conditions validate
    return (true);
}

void encrypt(string s, string key)
{
    for (int i = 0, l = strlen(s); i < l; i ++)
    {
        //if character is uppercase...
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            printf("%c", shift(s[i], 65, key));
        }
        //if cahracter is lowercase...
        else if (s[i] >= 'a' && s[i] <= 'z')
        {
            printf("%c", shift(s[i], 97, key));
        }
        //if character is non - alphabet
        else
        {
            printf("%c", s[i]);
        }
    }
}

char shift(char c, int d, string key)
{
    //shift formula based on ASCII
    int i = c - d;
    char k = key[i];
    if (d == 65)
    {
        return toupper(k);
    }
    else
    {
        return tolower(k);
    }

}