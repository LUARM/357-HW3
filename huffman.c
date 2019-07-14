#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include "huffman.h"
#include <assert.h>

#define MAX_HEIGHT 256


struct MinHeapNode* newnode(char data, unsigned freq) 
{ 
    struct MinHeapNode* temp  =   (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode)); 
  
    temp->left = temp->right = NULL; 
    temp->data = data; 
    temp->freq = freq; 
  
    return temp; 
} 

struct MinHeap* createMinHeap(unsigned capacity) 
  
{ 
    struct MinHeap* minHeap 
        = (struct MinHeap*)malloc(sizeof(struct MinHeap)); 
    minHeap->size = 0; 
  
    minHeap->capacity = capacity; 
  
    minHeap->array 
        = (struct MinHeapNode**)malloc(minHeap-> 
capacity * sizeof(struct MinHeapNode*)); 
    return minHeap; 
} 
  
void swap_Min(struct MinHeapNode** node1, 
                     struct MinHeapNode** node2)   
{ 
    struct MinHeapNode* t = *node1; 
    *node1 = *node2; 
    *node2 = t; 
} 

void min_Heap(struct MinHeap* minHeap, int idx) 
{ 
    int smallest = idx; 
    int left = 2 * idx + 1; 
    int right = 2 * idx + 2; 
  
    if (left < minHeap->size && minHeap->array[left]-> 
freq < minHeap->array[smallest]->freq) 
        smallest = left; 
  
    if (right < minHeap->size && minHeap->array[right]-> 
freq < minHeap->array[smallest]->freq) 
        smallest = right; 
  
    if (smallest != idx) { 
        swap_Min(&minHeap->array[smallest], 
                        &minHeap->array[idx]); 
        min_Heap(minHeap, smallest); 
    } 
} 

int if_One(struct MinHeap* minHeap) 
{ 
  
    return (minHeap->size == 1); 
} 

struct MinHeapNode* get_Min(struct MinHeap* minHeap) 
  
{ 
    struct MinHeapNode* temp = minHeap->array[0]; 
    minHeap->array[0] = minHeap->array[minHeap->size - 1]; 
  
    --minHeap->size; 
    min_Heap(minHeap, 0); 
  
    return temp; 

} 

void insert_Min(struct MinHeap* minHeap, 
                   struct MinHeapNode* minHeapNode) 
  
{ 
    int index;
    ++minHeap->size; 
    index = minHeap->size - 1; 
  
    while (index && minHeapNode->freq < minHeap->array[(index - 1) / 2]->freq) { 
  
        minHeap->array[index] = minHeap->array[(index - 1) / 2]; 
        index = (index - 1) / 2; 
    } 
  
    minHeap->array[index] = minHeapNode; 
} 


int if_Leaf(struct MinHeapNode* root)  
{ 
  
    return !(root->left) && !(root->right); 
} 
struct MinHeap* create_Heap(char data[], int freq[], int size) 
{ 
  
    struct MinHeap* minHeap = createMinHeap(size); 
    int index;
    for (index = 0; index < size; ++index) 
        minHeap->array[index] = newnode(data[index], freq[index]); 
  
    minHeap->size = size; 
    build_Heap(minHeap); 
  
    return minHeap; 
} 
void print_Code(struct MinHeapNode* root, int arr[], int top) 
{ 
    char buf[256] = "";
    if (root->left!= NULL) { 
        arr[top] = 0; 
        print_Code(root->left, arr, top + 1); 
    } 
    if (root->right!=NULL) { 
        arr[top] = 1; 
        print_Code(root->right, arr, top + 1); 
    } 

    if (if_Leaf(root)) {
        /*hex[z] = root->data;*/
        if (root->data < 15)
        {
         printf("0x0%x: ", root->data);  
      
        }
        else
        {
        printf("0x%x: ", root->data);
        }   
                if (transform_ints_to_string(arr, top, buf, sizeof buf) == -1) {
                    puts("not enough room");
                  }
                  else {
                    printf("%s\n", buf);
                   /* string_database[z] = buf;
                    z++;*/
                 }
    } 

}
void specialFree(struct HuffmanNode *node) {
    struct HuffmanNode *left, *right;
    if (node != NULL) { 
        left = node->left;
        right = node->right;
        specialFree(left);
        specialFree(right);
            if (left != 0){
                free(left);
            }
            if (right != 0){
                free(right);
            }
    }
    free(node);
}

int transform_ints_to_string(int const* data, int data_length,
    char* output, int output_length)
{
  int written ,length;  
  assert(data);
  assert(output);
  assert(data_length >= 0);
  assert(output_length >= 1);
  written = 0;
  for (; data_length; data_length--) {
    length = snprintf(output, output_length, "%d", *data++);
    if (length >= output_length) {
      return -1;
    }
    written += length;
    output += length;
    output_length -= length;
  }
  return written;
} 
bool comes_before(struct HuffmanNode *node1,struct HuffmanNode *node2, bool whichSort) {

    if (whichSort != true) 
    {
        if (node1->freq <= node2->freq)
        {
            return true;
        }
    }
    else {
        if ((node1->freq < node2->freq) || (node1->freq == node2->freq && node1->character < node2->character))
        {
            return true;
        }
    }
    return false;
}

struct HuffmanNode * insertNODE(struct HuffmanNode *Tree_root,struct HuffmanNode *createdNode, bool whichSort) {

    struct HuffmanNode *prevNode, *ThisNODE;
    bool root = false;
    root =whichSort;
    if (Tree_root == NULL){
        root = false;
    }
    else
    {
       root = comes_before(createdNode, Tree_root, root); 
    }
    if (root) 
    {
       createdNode->next = Tree_root;
       return createdNode;
    }
    prevNode = Tree_root;
    ThisNODE = Tree_root->next;

    while (ThisNODE != NULL) {

        if (!comes_before(createdNode, ThisNODE, whichSort)) {
             prevNode = ThisNODE;
            ThisNODE = ThisNODE->next;
        }
        else {

            prevNode->next = createdNode;
            createdNode->next = ThisNODE;
            return Tree_root;
        }
    }
    prevNode->next = createdNode;
    return Tree_root;
}

struct MinHeapNode* build_Huff(char data[], int freq[], int size)  
{ 
    struct MinHeapNode *left, *right, *top; 

    struct MinHeap* minHeap = create_Heap(data, freq, size); 

    while (!if_One(minHeap)) { 
        left = get_Min(minHeap);   
        right = get_Min(minHeap); 
        top = newnode('$', left->freq + right->freq); 
        top->left = left; 
        top->right = right; 
  
        insert_Min(minHeap, top); 
    } 
  
    return get_Min(minHeap); 
}

void unbit(struct HuffmanNode  *TreeRoot, uint8_t character, int fo, int fi,  uint32_t freqChar[],uint32_t CodeNUM[] )
{
  struct HuffmanNode *ThisNODE;
  uint8_t side,byteNUM;
    while (read(fi, &character, 1) > 0) 
    {
        while (byteNUM != 8) 
    {
        side = character & 128;
        if (side == 0) 
        {
        ThisNODE = ThisNODE->left;
        }
        else {
        ThisNODE = ThisNODE->right;
        }
        if (ThisNODE != NULL) 
        {
        if ((ThisNODE->right == NULL) && (ThisNODE->left == NULL)) 
        {
            if (CodeNUM[ThisNODE->character] < freqChar[ThisNODE->character]) 
            {
                write(fo, &ThisNODE->character, 1);
                CodeNUM[ThisNODE->character] += 1;
            }
            ThisNODE = TreeRoot;

        }
        }
        else 
        {
            ThisNODE = TreeRoot;
        }
        ++byteNUM;
        character = character << 1;
        }
        byteNUM = 0;
    }
}
struct HuffmanNode * freq(uint32_t *freqChar) {
    struct HuffmanNode *huffNode, *createdNode;
    int i;

    huffNode = NULL;
    i = 0;
    while (i < 256) {
        if (freqChar[i] != 0) {
            if (huffNode == NULL) {
                huffNode = malloc(sizeof(struct HuffmanNode));
                
                huffNode->left = NULL;
                huffNode->right = NULL;
                huffNode->next = NULL;
            
                huffNode->character = i;
                huffNode->freq = freqChar[i];
               
            }
            else {
                createdNode = malloc(sizeof(struct HuffmanNode));
                createdNode->left = NULL;
                createdNode->right = NULL;
                createdNode->next = NULL;

                createdNode->character = i;
                createdNode->freq = freqChar[i];
                
                huffNode = insertNODE(huffNode, createdNode, true);
            }
        }
        i++;
    }
    if (huffNode != NULL)
    {
        huffNode = MAKEhuff(huffNode);
    }
    
    return huffNode;
}

struct HuffmanNode * MAKEhuff(struct HuffmanNode *huffNode) {

    struct HuffmanNode  *ThisNODE;
    int  numAmount = 0;
    bool root = true;
    ThisNODE = huffNode;
    while (ThisNODE != NULL) {
        ++numAmount;
        ThisNODE = ThisNODE->next;
    }
    if (numAmount == 1) 
    {

        return huffNode;
    }
    while (true) 
    {
    struct HuffmanNode *sum_NODE = malloc(sizeof(struct HuffmanNode));
    sum_NODE->freq = huffNode->freq + huffNode->next->freq;    

    sum_NODE->left = huffNode;
    sum_NODE->right = huffNode->next;
    sum_NODE->next = NULL;
    if (numAmount == 2) 
    {
        huffNode = sum_NODE;
        break;
    }
    else {
        root = false;
        huffNode = huffNode->next->next;
        huffNode = insertNODE(huffNode, sum_NODE, root);
        --numAmount;
    }
    }
    return huffNode;
}
void build_Heap(struct MinHeap* minHeap) 
{ 
    int n = minHeap->size - 1; 
    int index; 
  
    for (index = (n - 1) / 2; index >= 0; --index) 
        min_Heap(minHeap, index); 
} 
void GETcode(struct HuffmanNode *node, uint64_t code, int side, uint64_t codes[]) {
    int index = 0;
    while(index < 0)
    {
       GETcode(node, 1, 0, code);
       index ++;
    } 
    if (node != NULL) { 
        if (side != 0) {
            if (node->left != NULL && node->right != NULL) {
                 if (side != -1){
                    code = (code * 10) + 1;
                 }   
                 else{
                    code = (code * 10);
                }
            }
            else {
                if (side == -1) {
                    codes[node->character] = code * 10;
                }
                else {
                    codes[node->character] = (code * 10) + 1;
                }
            }
        }
        GETcode(node->right, code, 1, codes);
         GETcode(node->left, code, -1, codes);
    }
}
void get_Huffman_Codes(char data[], int freq[], int size)  
{ 
  
    struct MinHeapNode* root 
        = build_Huff(data, freq, size); 
  
    int arr[MAX_HEIGHT], top = 0; 

    print_Code(root, arr, top); 
}

