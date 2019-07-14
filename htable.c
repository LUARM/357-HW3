#include <sys/types.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "huffman.h"
  
int main(int argc, char const *argv[]) 
{ 
    FILE *fp;
    long lSize;
    size_t len;
    char *buffer, charr_arr[256];
    int i, size = 0, freqq[256];
    
    fp = fopen ( argv[1] , "rb" );
    if(!fp)
    {
      perror("problem in file"),exit(1);
    }
    fseek( fp , 0L , SEEK_END);
    lSize = ftell( fp );
    rewind( fp );
    
    buffer = calloc( 1, lSize+1 );
    if( !buffer )
    {
       fclose(fp),fputs("memory alloc fails",stderr),exit(1); 
    } 

    if( 1!=fread( buffer , lSize, 1 , fp) )
    {
      fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);
    }
    unsigned char *str = buffer;
    int counts[256] = { 0 };
    len = strlen(str); 
    for (i = 0; i < len; i++) 
    {
        counts[(int)(str[i])]++;
    }

        for (i = 0; i < 256; i++) {
             if (counts[i] > 0){
           
        }
        if (counts[i]!= 0){
            charr_arr[size] = i;
            freqq[size] = counts[i];      
            size ++;
        }
    }
    fclose(fp);
    free(buffer);
    get_Huffman_Codes(charr_arr, freqq, size); 
    free(str);
   
    return 0; 
}
