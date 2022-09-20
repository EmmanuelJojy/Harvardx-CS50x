#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Prompt from user for name input
    string name = get_string("What is your name?\n");
    //printing hello <name>
    printf("hello, %s\n", name);
}