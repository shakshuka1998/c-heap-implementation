/*
*  Created by Guy Bernstein on 05/01/2024.
*/


/* Including necessary header files*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

/* Definitions of constants*/
#define MAX_CAPACITY 5000           /* Maximum capacity of each heap*/
#define ROOT 0                      /* Root index in the heap*/
#define MAX_LINE_LENGTH 30000       /* Maximum length of a line read from a file*/
#define MAX_HEAPS 10                /* Maximum number of heaps*/
#define MAX_FILENAME_LENGTH 260     /* Maximum length of the filename*/

/* Structure defining a Heap*/
typedef struct {
    int array[MAX_CAPACITY];  /* Array to store heap elements*/
    int size;                 /* Current number of elements in the heap*/
    int d;                    /* Degree of the heap*/
} Heap;

/* Function prototypes*/
void swap(int *x, int *y);
int child(int i, int k, int d);
int parent(int i, int d);
void dmaxHeapify(Heap *heap, int i);
int heapExtractMax(Heap *heap);
void insert(Heap *heap, int key);
void increaseKey(Heap *heap, int i, int key);
void buildMaxHeap(Heap *heap);
void delete(Heap *heap, int index);
int isNumber(const char *str);
void readHeapsFromFile(Heap heaps[], int *numHeaps, const char *fileName);
void printHeap(Heap *heap);
int getIntInput(const char *prompt, int min, int max);

/**
 * Swaps two integers.
 * @param x Pointer to the first integer
 * @param y Pointer to the second integer
 */
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

/**
 * Calculates the index of the k-th child of a node at index i in a d-ary heap.
 * This is based on the heap's structure where each node has d children.
 * @param i Index of the parent node.
 * @param k The k-th child to find (1st, 2nd, etc.).
 * @param d The degree of the heap (number of children each node has).
 * @return The index of the k-th child in the heap's array.
 */
int child(int i, int k, int d)
{
    return d * i + k;
}

/**
 * Finds the index of the parent of a node at index i in a d-ary heap.
 * This helps in navigating up the heap during heapify and insertion operations.
 * @param i Index of the child node.
 * @param d The degree of the heap.
 * @return The index of the parent node in the heap's array.
 */
int parent(int i, int d)
{
    return (i-1)/d;
}
/**
 * Ensures the max-heap property for a subtree rooted at a given node.
 * It's a key function to maintain the heap order property after insertions and deletions.
 * @param heap an index to the heap we will heapify
 * @param i Index of the root node of the subtree.
 */
void dmaxHeapify(Heap *heap, int i)
{
    int childrens;
    int largest;
    int j;
    while (1)
    {
        largest = i;
        /*find the largest of the childrens*/
        for (j = 1; j <= heap->d; ++j)
        {
            childrens = child(i, j, heap->d);
            if (childrens < heap->size && heap->array[childrens] > heap->array[largest])
                largest = childrens;
            
        }

        if (largest != i) 
        {
            swap(&heap->array[i], &heap->array[largest]);
            i = largest;
        }
        else
            break;
        
    }
}

/**
 * Extracts and removes the maximum element from the heap.
 * This function is critical for heap-based priority queue operations.
 * @param heap Pointer to the heap.
 * @return The maximum element in the heap.
 */
int heapExtractMax(Heap *heap)
{
    int max;
    if (heap->size < 1)
    {
        fprintf(stderr, "Error: heap underflow\n");
        exit(EXIT_FAILURE);
    }

    max = heap->array[ROOT];
    heap->array[ROOT] = heap->array[heap->size - 1];
    heap->size -= 1;
    dmaxHeapify(heap, ROOT);

    return max;
}

/**
 * Inserts a new key into the heap.
 * This function maintains the max-heap property by placing the new key at the end and then heapifying up.
 * @param heap Pointer to the heap.
 * @param key The key to insert.
 */
void insert(Heap *heap, int key)
{
    int i;
    if (heap->size == MAX_CAPACITY)
    {
        fprintf(stderr, "Error: heap overflow\n");
        exit(EXIT_FAILURE);
    }

    heap->array[heap->size] = key;
    i = heap->size;
    heap->size++;

    while (i > ROOT && heap->array[parent(i, heap->d)] < heap->array[i])
    {
        swap(&heap->array[i], &heap->array[parent(i, heap->d)]);
        i = parent(i, heap->d);
    }
}

/**
 * Increases the value of a key at a specific index in the heap.
 * This is essential for adjusting priority in a max-heap.
 * @param heap Pointer to the heap.
 * @param i Index of the key to increase.
 * @param key The new key value, which must be greater than the current value.
 */
void increaseKey(Heap *heap, int i, int key)
{
    
    if (key < heap->array[i])
    {
        fprintf(stderr, "Error: new key is smaller than current key\n");
        exit(EXIT_FAILURE);
    }

    heap->array[i] = key;
    while (i > 0 && heap->array[parent(i, heap->d)] < heap->array[i])
    {
        swap(&heap->array[i], &heap->array[parent(i, heap->d)]);
        i = parent(i, heap->d);
    }
}

/**
 * Builds a max-heap from an unordered array.
 * This function is crucial to initialize a valid max-heap structure from given data.
 * @param heap Pointer to the heap.
 */
void buildMaxHeap(Heap *heap)
{
    int i;
    for (i = (heap->size / heap->d)-1 ; i >= 0; i--)/*minus 1 because we start at index 0*/
        dmaxHeapify(heap, i);
}

/**
 * Deletes an element at a specific index in the heap.
 * This function uses a clever trick of increasing the key to the maximum possible value
 * and then extracting the max, effectively removing the desired element.
 * @param heap Pointer to the heap.
 * @param index Index of the element to be deleted.
 */
void delete(Heap *heap, int index)
{
    if (index >= heap->size)
    {
        fprintf(stderr, "Error: Index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    increaseKey(heap, index, INT_MAX); /* Increase key to maximum*/
    heapExtractMax(heap); /* Extract the new maximum, effectively deleting the original element*/
}

/**
 * Checks if the given string represents a valid integer.
 * @param str The string to check.
 * @return 1 if the string is a valid integer, 0 otherwise.
 */
int isNumber(const char *str) {
    /* Check if string is a number*/
    while (*str) 
    {
        if (!isdigit(*str) && *str != '-')
            return 0;
        
        str++;
    }
    return 1;
}


/**
 * Reads heap data from a file and populates an array of Heaps.
 * This function is crucial for initializing heaps with data from an external source.
 * @param heaps Array of Heap structures to be populated.
 * @param numHeaps Pointer to store the number of heaps read.
 * @param fileName Name of the file containing heap data.
 */
void readHeapsFromFile(Heap heaps[], int *numHeaps,const char *fileName)
{
    FILE *file =  fopen(fileName, "r");

    if (!file)
    {
        fprintf(stderr, "Error opening file.\n");
        exit(EXIT_FAILURE);
    }
    
    char line[MAX_LINE_LENGTH];
    int heapIndex = 0;
    while (fgets(line, MAX_LINE_LENGTH, file) && heapIndex < MAX_HEAPS)
    {
        char *token = strtok(line, " ");
        heaps[heapIndex].size = 0;

        while (token != NULL)
        {
            heaps[heapIndex].array[heaps[heapIndex].size] = atoi(token);
            heaps[heapIndex].size++;
            token = strtok(NULL, " ");
        }

        heapIndex++;
    }

    *numHeaps = heapIndex;
    fclose(file);
}

/**
 * Prints all elements of a heap.
 * This is used for displaying the current state of a heap.
 * @param heap Pointer to the heap to be printed.
 */
void printHeap(Heap *heap)
{
    int i;
    for (i = 0; i < heap->size; i++)
        printf("%d ", heap->array[i]);
    printf("\n");
}

/**
 * Prompts the user for integer input within a specified range.
 * This function ensures that user input is valid and within the required bounds.
 * @param prompt The prompt message to display to the user.
 * @param min Minimum allowable value.
 * @param max Maximum allowable value.
 * @return The validated integer input from the user.
 */
int getIntInput(const char *prompt, int min, int max)
{
    char input[100];
    int number;
    while (1) 
    {
        printf("%s", prompt);
        scanf("%s", input);

        if (isNumber(input))
        {
            number = atoi(input);
            if (number >= min && number <= max)
                return number;
        }
        printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
    }
}

/**
 * The main function where the program execution begins.
 * This function orchestrates reading heaps from a file, performing heap operations,
 * and interacting with the user.
 */
int main(int argc, const char * argv[])
{
    Heap *selectedHeap;
    Heap heaps[MAX_HEAPS];
    int numHeaps;
    int selectedHeapIndex;
    int key, index,choice;
    int d;
    char fileName[MAX_FILENAME_LENGTH];
    int i;
    /*read file*/
    printf("Enter the name of the file containing heap data: ");
    scanf("%s", fileName);
    readHeapsFromFile(heaps, &numHeaps, fileName);
    
    
    /*print arrays*/
    printf("Available arrays:\n");
    for (i = 0; i < numHeaps; i++)
    {
        printf("array %d: ", i + 1);
        printHeap(&heaps[i]);
    }
    
    /*pick array*/
    selectedHeapIndex = getIntInput("\nSelect an array number (1 to number of heaps): ", 1, numHeaps) - 1;
    
    
    /*get d*/
    d = getIntInput("Enter the degree (d) of the heap (greater than 1): ", 1, INT_MAX);
   
    /*build heap*/
    selectedHeap = &heaps[selectedHeapIndex];
    selectedHeap->d = d;
    buildMaxHeap(selectedHeap);

    /*start the program*/
    while (1)
    {
        /*print current heap*/
        printf("\nYour array with the d=%d is now heaped like this:\n",d);
        printHeap(selectedHeap);
        
        printf("\nChoose an operation:\n");
        printf("1. Insert Key\n");
        printf("2. Increase Key\n");
        printf("3. Extract Max\n");
        printf("4. Delete Key\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        choice = getIntInput("", 1, 5);

        
        switch (choice)
        {
            case 1:
                key = getIntInput("Enter the key to insert: ", INT_MIN, INT_MAX);
                insert(selectedHeap, key);
                break;
            case 2:
                index = getIntInput("Enter the index: ", 0, selectedHeap->size - 1);
                key = getIntInput("Enter the new key: ", INT_MIN, INT_MAX);
                increaseKey(selectedHeap, index, key);
                break;
            case 3:
                if (selectedHeap->size > 0)
                {
                    key = heapExtractMax(selectedHeap);
                    printf("Extracted Max: %d\n", key);
                }
                else
                    printf("Heap is empty!\n");
                break;
            case 4:
                index = getIntInput("Enter the index of the key to delete: ", 0, selectedHeap->size - 1);
                delete(selectedHeap, index);
                break;
            case 5:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
     
    return 0;
}

