#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <assert.h>

struct MinHeapNode { 

    char data;
    unsigned freq; 
    struct MinHeapNode *left, *right;
}; 
struct HuffmanNode {
    uint8_t character;
    uint32_t freq;
    struct HuffmanNode  *left,*right,*next;
};
struct MinHeap { 
    unsigned size; 
    unsigned capacity; 
    struct MinHeapNode** array; 
};

struct MinHeapNode* newnode(char data, unsigned freq);
struct MinHeap* createMinHeap(unsigned capacity);
void swap_Min(struct MinHeapNode** a, struct MinHeapNode** b);
void min_Heap(struct MinHeap* minHeap, int idx);
int if_One(struct MinHeap* minHeap);
struct HuffmanNode * freq(uint32_t *freqChar);
struct HuffmanNode * MAKEhuff(struct HuffmanNode *TreeRoot);
struct MinHeapNode* get_Min(struct MinHeap* minHeap);
int transform_ints_to_string(int const* data, int data_length,
    char* output, int output_length);
void insert_Min(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode);
void build_Heap(struct MinHeap* minHeap);
int if_Leaf(struct MinHeapNode* root);
void GETcode(struct HuffmanNode *node, uint64_t code, int side, uint64_t codes[]);
void specialFree(struct HuffmanNode *TreeRoot);
void GETcode(struct HuffmanNode *node, uint64_t code, int side, uint64_t codes[]);
void unbit(struct HuffmanNode  *TreeRoot, uint8_t character, int fo, int fi,  uint32_t freqChar[],uint32_t CodeNUM[] );
struct MinHeap* create_Heap(char data[], int freq[], int size) ;
struct MinHeapNode* build_Huff(char data[], int freq[], int size) ;
void print_Code(struct MinHeapNode* root, int arr[], int top) ;
void create_codes(struct HuffmanNode *TreeRoot, uint64_t codes[]);
void special_free(struct HuffmanNode *node, int fi, int fo);
void get_Huffman_Codes(char data[], int freq[], int size);






