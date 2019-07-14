#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "huffman.h"

int main (int argc, char **argv) {

    int i, fi, fo = 0, size32, fc;
    uint32_t freqChar[256], count = 0;
    struct HuffmanNode *TreeRoot;
    uint64_t codes[256];
    uint32_t  character, NumBytes, writeByte;
    char temp[256], *charCode[256];
    size32 = sizeof(uint32_t);

     if (argc < 2) 
     {
        fprintf( stderr, "not enough arguments\n");
        return 0;
     }
    while (i < 256)
    {
        freqChar[i] = 0;
        codes[i] = 0;
        charCode[i] = NULL;
        i++;
    }
    fi = open(argv[1], O_RDONLY);
    if (fi == -1) {
        fprintf( stderr, "incorect input file\n");
        return 0;
    }
    if (argc > 2) {
         fo = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (fo == -1) 
            {
                fprintf( stderr, "cant write filem\n");
                return 0;
            } 
    }
    fc = open(argv[1], O_RDONLY);
    if (fc == -1) {
        fprintf( stderr, "incorect input file\n");
        return 0;
    }
    else{
        while (read(fc, &character, 1) > 0) {  
                if (!freqChar[(int)character]){
                     count++;
                }
                  freqChar[(int)character]++;
            }
    } 
    TreeRoot = freq(freqChar);
    GETcode(TreeRoot, 1, 0, codes);
    write(fo, &count, size32);
    i = 0;
    while (i < 256) {
         if (freqChar[i] != 0) 
        {
            character = i;
            write(fo, &character, 1);
            write(fo, &freqChar[i], size32);
        }
        if (codes[i] != 0) 
        {
            sprintf(temp, "%lu", codes[i]);
            charCode[i] = malloc(strlen(temp));
            strcpy(charCode[i], &temp[1]);
        }
        
        i++;
    }
    if (count > 1) 
    {
        character = 0;
        while (read(fi, &character, 1) > 0) 
        {
            i = 0;
            while(i < strlen(charCode[(int)character]))
            {
                if (charCode[character][i] == 49)
                {
                    writeByte = writeByte | 1;
          
                }
                ++NumBytes;
                if (NumBytes == 8)
                {
                    write(fo, &writeByte, 1);
                    NumBytes = 0, writeByte = 0;
                }
                else 
                {
                    writeByte = writeByte << 1;
                }
                i++;

            }
        }
        if (NumBytes != 0) 
        {
                while (NumBytes < 7) 
                {
                    writeByte = writeByte << 1;
                    ++NumBytes;
                }
                write(fo, &writeByte, 1);
        }
    }
    close(fi);
    close(fo);
    close(fc);
    i = 0;
    while (i < 256) 
        {
        if (charCode[i] != 0){
            free(charCode[i]);
        }
        i++;
    }
    specialFree(TreeRoot); 
    return 0;
}

