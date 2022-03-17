//Nicholas Girmes, Michael Babinec, Quinn Curry, John Bither
//CPSC351
//Project Assignment 3

//Includes
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <stdlib.h>

//Global Variables
#define SIZE (sizeof(list)/sizeof(*list))
int list[] = {7, 12, 19, 3, 18, 4, 2, -5, 6, 15, 8};
int result[SIZE] = {0};

//Structs for passing array info
typedef struct{
    int *sub_array;
    unsigned int size;
} sorting_thread_parameters;

typedef struct{
    sorting_thread_parameters left;
    sorting_thread_parameters right;
} merging_thread_parameters;

//Function creates threads for sorting and merging
void pthread_create(){
    //fork();
}

//Main Function
int main(int argc, char *argv[])
{
    sorting_thread_parameters *params_left = malloc(sizeof(sorting_thread_parameters));
    params_left->sub_array = list;
    params_left->size = SIZE/2;
    //Pass first unsorted array to pthread_create and sort using an in-place sort
    //pthread_create(params_left);
    sorting_thread_parameters *params_right = malloc(sizeof(sorting_thread_parameters));
    params_right->sub_array = list + params_left->size;
    params_right->size = SIZE - params_left->size;
    //Pass second unsorted array to pthread_create and sort using an in-place sort
    //pthread_create(params_right);
    //wait(0);
    merging_thread_parameters *params_merge = malloc(sizeof(sorting_thread_parameters));
    params_merge->left = *params_left;
    params_merge->right = *params_right;
    //pthread_create(params_merge);
    //Parent thread to output sorted array
    //printf("Sorted: " + result);
    return 0;
}