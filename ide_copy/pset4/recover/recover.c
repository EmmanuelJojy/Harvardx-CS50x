#include <stdio.h>
#include <stdlib.h>

// stdint.h for implementing BYTE
#include <stdint.h>

// BYTE type unsigned int of size 8 bits
// uint8_t reprsent unsigned int of 8 bits
typedef uint8_t BYTE;

// start() checks if next block is start of jpeg
// 0xff - 0xd8 - 0xff - 0xe_
// returns 1 if start else 0
int start(BYTE buffer[]);

int main(int argc, char *argv[])
{
    // check if user provides filename
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    // BYTE array for one block
    // 1 Block = 512 bytes = 512 * 8 bits
    BYTE buffer[512];

    //img represent output jpg
    FILE *img;

    //flag is 0 if no jpg's found
    int flag = 0;

    // fname represent output file name
    // ###.jpg and \0
    char fname[8];

    // opening input
    FILE *file = fopen(argv[1], "r");

    // fread syntax check in walkthrough
    // fread returns 0 if data_size is less than 512
    while (fread(buffer, 512, 1, file))
    {
        // check if start of new jpg
        if (start(buffer))
        {
            // check if first jpg
            if (flag == 0)
            {
                // write to fname filename
                // filename : ###.jpg\0
                sprintf(fname, "%03i.jpg", flag);

                //img type FILE* to wrote to new file
                img = fopen(fname, "w");

                // fwrite
                fwrite(buffer, 512, 1, img);
            }
            else
            {
                // if not first jpg close previous one
                fclose(img);
                sprintf(fname, "%03i.jpg", flag);
                //same as prev
                img = fopen(fname, "w");
                fwrite(buffer, 512, 1, img);
            }
            flag++;
        }
        else
        {
            // blocks from writing if first block is not jpg
            if (flag > 0)
            {
                fwrite(buffer, 512, 1, img);
            }
        }
    }
    // close all open files
    fclose(img);
    fclose(file);
}

int start(BYTE buffer[])
{
    //check question page for explanation of jpg start
    if (buffer[0] != 0xff || buffer[1] != 0xd8 || buffer[2] != 0xff)
    {
        return 0;
    }
    if ((buffer[3] & 0xf0) != 0xe0)
    {
        return 0;
    }
    return 1;
}