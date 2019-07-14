#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "huffman.h"

int main (int argc, char **argv) {
    int i, fi, fo = 0,  size32;
    uint32_t freqChar[256], CodeNUM[256], count = 0;
    struct HuffmanNode *TreeRoot;
    uint8_t character;
    size32 = sizeof(uint32_t);

    if (argc < 2) 
    {
        fprintf( stderr, "not enough arguments\n");
        return 0;
    }
    if (argc > 2) 
    {
        fi = open(argv[1], O_RDONLY);
        if (fi == -1) 
        {
        fprintf( stderr, "incorect input file\n");
        return 0;
        }
        for (i = 0; i < 256; i++) 
        {
        freqChar[i] = 0;
        CodeNUM[i] = 0;
        }
        fo = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (fo == -1) 
        {
        fprintf( stderr, "cant write filem\n");
        return 0;
        }

    }
    if (read(fi, &count, size32) <= 0) 
    {
        fprintf( stderr, "incorect input file\n");
        return 0;
    }
    for (i = 0; i < count; i++) 
    {
        if (read(fi, &character, 1) <= 0) 
        {
            fprintf( stderr, "incorect input file\n");
            return 0;
        }
        if (read(fi, &freqChar[character], size32) <= 0) {
            fprintf( stderr, "incorect input file\n");
            return 0;
        }
    }
    TreeRoot = freq(freqChar);
    if (count == 1) 
    {   
        i = 0;
        while (i < TreeRoot->freq) 
        {
            write(fo, &TreeRoot->character, 1);
            i++;
        }
    }
    else 
    {
    unbit(TreeRoot, character, fo, fi, freqChar,CodeNUM);    
    }
    close(fi);
    close(fo);
    specialFree(TreeRoot);

    return 0;
}
