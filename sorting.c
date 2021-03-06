// Nicholas Girmes, Michael Babinec, Quinn Curry, John Bither
// CPSC351
// Project Assignment 3

// Includes
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <stdlib.h>

// Global Variables
#define SIZE (sizeof(list) / sizeof(*list))
int list[] = {7, 12, 19, 3, 18, 4, 2, -5, 6, 15, 8};
int result[SIZE] = {0};
pid_t pid;

// Structs for passing array info
typedef struct
{
    int* sub_array;
    unsigned int size;
} sort_parameters;

typedef struct
{
    int* left;
    int* right;
} merge_parameters;

// Compare function for qsort()
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// Function sorts beginning with passed index to a certain passed size
void sort_array(sort_parameters *params)
{
    qsort(params->sub_array, params->size, sizeof(int), compare);
}

// Function merges two arrays
void merge_array(merge_parameters *params)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (*params->left < *params->right || *params->right == 0)
        {
            result[i] = *params->left;
            params->left++;
            continue;
        }
        else if (*params->right < *params->left || *params->left == 0)
            result[i] = *params->right;
            params->right++;
    }
}

// Function creates threads for sorting and merging
void pthread_create(sort_parameters *sort_params, merge_parameters *merge_params)
{
    if (merge_params == NULL)
        sort_array(sort_params);
    else
        merge_array(merge_params);
}

// Main Function
int main(int argc, char *argv[])
{
    // Print unsorted array
    printf("Unsorted: ");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", list[i]);
    }

    // Create instance of sorting thread struct for first half of array and allocate memory
    sort_parameters *params_left = malloc(sizeof(sort_parameters));

    // Set variables for first half of array
    params_left->sub_array = list;
    params_left->size = SIZE / 2;

    // Call pthread_create for first half of array
    pthread_create(params_left, NULL);
    // Create instance of sorting thread struct for second half of array and allocate memory
    sort_parameters *params_right = malloc(sizeof(sort_parameters));

    // Set variables for second half of array
    params_right->sub_array = list + params_left->size;
    params_right->size = SIZE - params_left->size;

    // Call pthread_create for first half of array
    pthread_create(params_right, NULL);

    // Print halves sorted array
    printf("\nHalves sorted: ");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", list[i]);
    }

    merge_parameters *params_merge = malloc(sizeof(merge_parameters));

    // Set pointers to merge
    params_merge->left = params_left->sub_array;
    params_merge->right = params_right->sub_array;

    // Call pthread_create to merge
    pthread_create(NULL, params_merge);

    // Free space used with malloc
    free(params_left);
    free(params_right);
    free(params_merge);

    // Print sorted array
    printf("\nSorted: ");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}