//
// Created by MingHuai Tsai on 20/9/19.
//

#ifndef ASSIGNMENT2_FUNCTION_H
#define ASSIGNMENT2_FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>

typedef struct find_index_results {
    int *index_array;
    int length;
}find_index_result;

void swap(int*, int, int);
int verify(int*, int);
int* get_array(int);
int* get_worst_case_array(int);
int* get_best_case_array(int);
int* copy_array(int*, int);
void show_array(int*, int);
int find_max(int*, int);
int find_min(int*, int);
find_index_result* find_index_function(int*, int, int);

void swap(int *ary, int index, int index2) {
    int temp = ary[index];
    ary[index] = ary[index2];
    ary[index2] = temp;
}

int verify(int *ary, int len) {
    for(int i = 0; i < len-1; i++) {
        if(ary[i] > ary[i+1]) {
            return 0;
        }
    }
    return 1;
}

int * get_array(int len) {
    int* array = malloc(len * sizeof(int));
    for(int i = 0; i < len; i++) {
        array[i] = rand() % INT32_MAX;
    }
    return array;
}

// Worst case means the element in index "0" is the biggest, and in index "len-1" is the smallest
int * get_worst_case_array(int len) {
    int *array = malloc(len * sizeof(int));
    for(int i = 0; i < len; i++){
        array[i] = len - i;
    }
    return array;
}

// Worst case means the element in index "0" is the smallest, and in index "len-1" is the biggest
int * get_best_case_array(int len) {
    int *array = malloc(len * sizeof(int));
    for(int i = 0; i < len; i++) {
        array[i] = i+1;
    }
    return array;
}

// Deep copy
int * copy_array(int *origin, int len) {
    int *b = malloc(len * sizeof(int));
    memcpy(b, origin, len * sizeof(int));
    return b;
}

void show_array(int *array, int len){
    for(int i = 0; i < len; i++){
        printf("%d,", array[i]);
    }
    printf("\n");
}

// return the index of the array which is maximum
int find_max(int *array, int len){
    int max = 0;
    for(int i = 1; i < len; i++){
        if(array[i] > array[max]){
            max = i;
        }
    }
    return max;
}

int find_min(int *array, int len){
    int min = 0;
    for(int i = 1; i < len; i++){
        if(array[i] < array[min]){
            min = i;
        }
    }
    return min;
}

find_index_result * find_index_function(int *array, int len, int key) {

    find_index_result *fi_results = malloc(sizeof(find_index_result));
    fi_results->length = 0;
    for(int i = 0; i < len; i++) {
        if(array[i] == array[key]) {
            fi_results->length++;
        }
    }

    fi_results->index_array = (int *)malloc(fi_results->length * sizeof(int));
    int count = 0;
    for(int i = 0; i < len; i++) {
        if(array[i] == array[key]) {
            fi_results->index_array[count] = i;
            count++;
        }
    }

    return fi_results;
}

#endif //ASSIGNMENT2_FUNCTION_H
