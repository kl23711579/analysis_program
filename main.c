#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "function.h"

//set loopstime and size_times
// example => loop_times = 10, size_times = 50
// do loop for 11 times, array size from 0 to 500 => 0, 50, 100, 150 ..., 450, 500
#define LOOP_TIMES 50
#define SIZE_TIMES 1000

#define AVERAGE_TIMES 10

typedef struct sort_results {
    long long count;
    int *sorted_array;
} sort_result;

typedef sort_result* (*sort_function)(int*, int);
typedef int* (*get_array_function)(int);

// get_array_approaches: 0 -> random array, 1 -> worst case array, 2 -> best case array
// sort_approaches: 0 -> cocktail_shaker_sort, 1 -> insertion_sort
typedef struct function_structs{
    sort_function *sort_functions;
    get_array_function *get_array_functions;
    int get_array_approaches;
    int *sort_approaches;
} function_struct;

// array -> store array
// basic_operation_array -> store the basic operation which have the same index with array
// index -> count index
typedef struct permutation_results {
    int **array;
    int *basic_operation_array;
    int index;
} permutation_result;

sort_result* cocktail_shaker_sort(int*, int);
sort_result* insertion_sort(int*, int);
void measure_function(function_struct, char*);
void compare_function(function_struct, char*);
void permutation(sort_function, int);
permutation_result permutation_test(int*, int, int, sort_function, permutation_result*);

int main() {

    sort_function sort_functions[] = {cocktail_shaker_sort, insertion_sort};
    get_array_function get_array_functions[] = {get_array, get_worst_case_array, get_best_case_array};

    // set function pointer
    function_struct *funcs = malloc(sizeof(function_struct));
    funcs->sort_functions = malloc(2 * sizeof(sort_function));
    for(int i = 0; i < 2; i++) {
        funcs->sort_functions[i] = sort_functions[i];
    }
    funcs->get_array_functions = malloc(3 * sizeof(get_array_function));
    for(int i = 0;i < 3; i++) {
        funcs->get_array_functions[i] = get_array_functions[i];
    }

    // ensure the array is random
    srand(time(0));

    //permutation Test
    //int largest_array_size = 1;
    //permutation(sort_functions[0], largest_array_size); // cocktail
    //permutation(sort_functions[1], largest_array_size); // insertion

    // Cocktail Shaker Sort
    printf("===================================\n");
    printf("=======Cocktail Shaker Sort========\n");
    printf("===================================\n");

    // Average Case
    printf("===================================\n");
    printf("===========Average Case============\n");
    printf("===================================\n");

    funcs->sort_approaches = (int *)malloc(1 * sizeof(int));
    funcs->sort_approaches[0] = 0;
    funcs->get_array_approaches = 0;
    measure_function(*funcs, "avg_result_cocktail.txt");

    // The worst case
    printf("===================================\n");
    printf("=======The Worst Case Start========\n");
    printf("===================================\n");

    funcs->sort_approaches = (int *)malloc(1 * sizeof(int));
    funcs->sort_approaches[0] = 0;
    funcs->get_array_approaches = 1;
    measure_function(*funcs, "worst_result_cocktail.txt");

    // The best case
    printf("===================================\n");
    printf("=======The Best Case  Start========\n");
    printf("===================================\n");

    funcs->sort_approaches = (int *)malloc(1 * sizeof(int));
    funcs->sort_approaches[0] = 0;
    funcs->get_array_approaches = 2;
    measure_function(*funcs, "best_result_cocktail.txt");

    //Insertion Sort
    printf("===================================\n");
    printf("==========Insertion sort===========\n");
    printf("===================================\n");

    // Average Case
    printf("===================================\n");
    printf("===========Average Case============\n");
    printf("===================================\n");

    funcs->sort_approaches = (int *)malloc(1 * sizeof(int));
    funcs->sort_approaches[0] = 1;
    funcs->get_array_approaches = 0;
    measure_function(*funcs, "avg_result_insertion.txt");

    // The worst case
    printf("===================================\n");
    printf("=======The Worst Case Start========\n");
    printf("===================================\n");

    funcs->sort_approaches = (int *)malloc(1 * sizeof(int));
    funcs->sort_approaches[0] = 1;
    funcs->get_array_approaches = 1;
    measure_function(*funcs, "worst_result_insertion.txt");

    // The Best case
    printf("===================================\n");
    printf("=======The Best Case  Start========\n");
    printf("===================================\n");

    funcs->sort_approaches = (int *)malloc(1 * sizeof(int));
    funcs->sort_approaches[0] = 1;
    funcs->get_array_approaches = 2;
    measure_function(*funcs, "best_result_insertion.txt");

    //Comparison
    printf("===================================\n");
    printf("============Comparison=============\n");
    printf("===================================\n");

    //Comparison
    printf("===================================\n");
    printf("=============Average===============\n");
    printf("===================================\n");

    funcs->sort_approaches = (int *)malloc(2 * sizeof(int));
    funcs->sort_approaches[0] = 0;
    funcs->sort_approaches[1] = 1;
    funcs->get_array_approaches = 0;
    compare_function(*funcs, "avg_result_comparison.txt");

    //Comparison
    printf("===================================\n");
    printf("============Worst Case=============\n");
    printf("===================================\n");

    funcs->sort_approaches = (int *)malloc(2 * sizeof(int));
    funcs->sort_approaches[0] = 0;
    funcs->sort_approaches[1] = 1;
    funcs->get_array_approaches = 1;
    compare_function(*funcs, "worst_result_comparison.txt");

    //Comparison
    printf("===================================\n");
    printf("=============BestCase==============\n");
    printf("===================================\n");

    funcs->sort_approaches = (int *)malloc(2 * sizeof(int));
    funcs->sort_approaches[0] = 0;
    funcs->sort_approaches[1] = 1;
    funcs->get_array_approaches = 2;
    compare_function(*funcs, "best_result_comparison.txt");

    return 0;
}

sort_result* cocktail_shaker_sort(int *ary, int len) {
    int swapped = 0;
    long long count = 0;
    sort_result *cs1 = malloc(sizeof(sort_result));

    do {
        swapped = 0;
        for(int i = 0; i <= len - 2; i++) {
            count++;
            if(ary[i] > ary[i+1]) {
                swap(ary, i, i + 1);
                swapped = 1;
                count++;
            }
        }
        if(!swapped){
            cs1->count = count;
            cs1->sorted_array = malloc(len * sizeof(int));
            cs1->sorted_array = ary;
            return cs1;
        }
        swapped = 0;
        for(int i = len-2; i >= 0; i--){
            count++;
            if(ary[i] > ary[i+1]) {
                swap(ary, i, i + 1);
                swapped = 1;
                count++;
            }
        }
    } while (swapped);

    cs1->count = count;
    cs1->sorted_array = malloc(len * sizeof(int));
    cs1->sorted_array = ary;
    return cs1;
}

sort_result* insertion_sort(int *ary, int len) {
    int i = 0, j;
    long long count = 0;
    sort_result *cs1 = malloc(sizeof(sort_result));

    while(i < len){
        j = i;
        while(j > 0){
            count++;
            if(ary[j-1] > ary[j]) {
                swap(ary, j - 1, j);
                j = j - 1;
                count++;
            } else {
                break;
            }
        }
        i = i + 1;
    }

    cs1->count = count;
    cs1->sorted_array = malloc(len * sizeof(int));
    cs1->sorted_array = ary;

    return cs1;
}

void measure_function(function_struct funcs, char *filename) {
    FILE *fptr;
    int *a;
    int len = 0;
    int is_sorted; // 0 -> unsort, 1 -> sort
    double total_t, sum_total_t;
    long long sum_count;
    struct timespec start_t, end_t;
    sort_result *sort_results;

    // Print
    printf("Length \t  Time \t    Basic Operation\n");

    //Open file
    if ((fptr = fopen(filename,"w")) == NULL){
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    for(int i = 0; i <= LOOP_TIMES; i++) {
        sum_total_t = 0;
        sum_count = 0;
        for (int j = 0; j < AVERAGE_TIMES; j++) {
            // Get size
            len = i * SIZE_TIMES;

            // Get array
            a = funcs.get_array_functions[funcs.get_array_approaches](len);

            // Start
            if (clock_gettime(CLOCK_MONOTONIC, &start_t) == -1) exit(0);
            sort_results = funcs.sort_functions[funcs.sort_approaches[0]](a, len);
            if (clock_gettime(CLOCK_MONOTONIC, &end_t) == -1) exit(0);

            total_t = ((double) end_t.tv_sec + 1.0e-9 * (double) end_t.tv_nsec) -
                      ((double) start_t.tv_sec + 1.0e-9 * (double) start_t.tv_nsec);
            //printf("Index = %d is done Time = %.7f Count = %lli \n", len, total_t, sort_results->count);
            sum_total_t += total_t;
            sum_count += sort_results->count;

            // verify array is sorted
            is_sorted = verify(sort_results->sorted_array, len);
            if (!is_sorted) {
                printf("Index = %d Is not sorted\n", len);
            }

            free(a);
        }
        // do average
        sum_total_t /= AVERAGE_TIMES;
        sum_count /= AVERAGE_TIMES;

        // Printf
        printf("%5d \t %.7f \t %10lli\n", len, sum_total_t, sum_count);

        // output file
        fprintf(fptr, "%d %.7f %lli\n", len, sum_total_t, sum_count);
    }

    // close file
    fclose(fptr);
}

void compare_function(function_struct funcs, char *filename) {
    FILE *fptr;
    int *array_a, *array_b;
    int len = 0;
    int is_sorted; // 0 -> unsort, 1 -> sort
    double total_t, total_t_b, sum_total_t, sum_total_t_b;
    long long sum_count, sum_count_b;
    struct timespec start_t, end_t, start_t_b, end_t_b;
    sort_result *s_results, *s_results_b;

    // Print
    printf("Length \t    Time \t    Time \t  Operation \tOperation \n");

    //Open file
    if ((fptr = fopen(filename,"w")) == NULL){
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    for(int i = 0; i <= LOOP_TIMES; i++) {
        sum_total_t = 0;
        sum_total_t_b = 0;
        sum_count = 0;
        sum_count_b = 0;
        for (int j = 0; j < AVERAGE_TIMES; j++) {
            // Get size
            len = i * SIZE_TIMES;

            // Get array
            array_a = funcs.get_array_functions[funcs.get_array_approaches](len);
            array_b = copy_array(array_a, len);

            // Start array_a
            if (clock_gettime(CLOCK_MONOTONIC, &start_t) == -1) exit(0);
            s_results = funcs.sort_functions[funcs.sort_approaches[0]](array_a, len);
            if (clock_gettime(CLOCK_MONOTONIC, &end_t) == -1) exit(0);
            total_t = ((double) end_t.tv_sec + 1.0e-9 * (double) end_t.tv_nsec) -
                      ((double) start_t.tv_sec + 1.0e-9 * (double) start_t.tv_nsec);
            //printf("A Index = %d is done Time = %.7f Count = %lli \n", len, total_t, s_results->count);
            sum_total_t += total_t;
            sum_count += s_results->count;

            // start array_b
            if (clock_gettime(CLOCK_MONOTONIC, &start_t_b) == -1) exit(0);
            s_results_b = funcs.sort_functions[funcs.sort_approaches[1]](array_b, len);
            if (clock_gettime(CLOCK_MONOTONIC, &end_t_b) == -1) exit(0);
            total_t_b = ((double) end_t_b.tv_sec + 1.0e-9 * (double) end_t_b.tv_nsec) -
                        ((double) start_t_b.tv_sec + 1.0e-9 * (double) start_t_b.tv_nsec);
            //printf("B Index = %d is done Time = %.7f Count = %lli \n", len, total_t_b, s_results_b->count);
            //printf("\n");
            sum_total_t_b += total_t_b;
            sum_count_b += s_results_b->count;

            // verify array is sorted, two arrays all need to be verified
            is_sorted = verify(s_results->sorted_array, len);
            if (!is_sorted) {
                printf("Index = %d Is not sorted\n", len);
            }
            is_sorted = verify(s_results_b->sorted_array, len);
            if (!is_sorted) {
                printf("Index = %d Is not sorted\n", len);
            }

            free(array_a);
            free(array_b);
        }
        // do average
        sum_total_t /= AVERAGE_TIMES;
        sum_count /= AVERAGE_TIMES;
        sum_total_t_b /= AVERAGE_TIMES;
        sum_count_b /= AVERAGE_TIMES;

        // Print
        printf("%5d \t %8.7f \t %.7f \t %10lli\t %10lli \n", len, sum_total_t, sum_total_t_b, sum_count, sum_count_b);

        // output file
        fprintf(fptr, "%d %.7f %lli %.7f %lli\n", len, sum_total_t, sum_count, sum_total_t_b, sum_count_b);
    }

    // close file
    fclose(fptr);
}

void permutation(sort_function sort_functions, int p_test_times){
    //Permutation test
    int *p_test_array;

    permutation_result *p_results = malloc(sizeof(permutation_result));
    p_results->index = 0;

    find_index_result *fi_result;

    for(int array_size = 1; array_size <= p_test_times; array_size++){
        int size = 1;
        for(int j = 1; j <= array_size; j++){
            size *= j;
        }

        p_results->array = (int **)malloc(size * sizeof(int *));
        p_results->basic_operation_array = (int *)malloc(size * sizeof(int));

        p_test_array = get_worst_case_array(array_size);
        *p_results = permutation_test(p_test_array, 0, array_size, sort_functions, p_results);

        printf("\n");
        printf("=====================\n");
        printf("========Max==========\n");
        printf("=====Size = %d=======\n", array_size);
        printf("=====================\n");

        int max_in_array_index = find_max(p_results->basic_operation_array, size);
        printf("max_in_array_index = %d\n", max_in_array_index);
        show_array(p_results->array[max_in_array_index], array_size);
        printf("Count = %d\n", p_results->basic_operation_array[max_in_array_index]);

        fi_result = find_index_function(p_results->basic_operation_array, p_results->index, max_in_array_index);
        for(int j = 0; j < fi_result->length; j++) {
            printf("Index = %d \t Array = ", fi_result->index_array[j]);
            show_array(p_results->array[fi_result->index_array[j]], array_size);
            printf("\n");
        }

        // initial fi_result
        free(fi_result->index_array);
        free(fi_result);

        printf("=====================\n");
        printf("========Min==========\n");
        printf("=====Size = %d=======\n", array_size);
        printf("=====================\n");

        int min_in_array_index = find_min(p_results->basic_operation_array, size);
        printf("max_in_array_index = %d\n", min_in_array_index);
        show_array(p_results->array[min_in_array_index], array_size);
        printf("Count = %d\n", p_results->basic_operation_array[min_in_array_index]);

        fi_result = find_index_function(p_results->basic_operation_array, p_results->index, min_in_array_index);
        for(int j = 0; j < fi_result->length; j++) {
            printf("Index = %d \t Array = ", fi_result->index_array[j]);
            show_array(p_results->array[fi_result->index_array[j]], array_size);
            printf("\n");
        }

        printf("=====================\n");
        printf("=======next==========\n");
        printf("=====================\n");

        // Initial
        free(p_test_array);
        free(p_results->array);
        free(p_results->basic_operation_array);
        p_results->index = 0;
        free(fi_result->index_array);
        free(fi_result);
    }

    free(p_results);
}

permutation_result permutation_test(int *array, int index, int len, sort_function sort_functions, permutation_result *p_results){
    if(index == len-1){
        struct timespec start_t, end_t;
        double total_t;
        int is_sorted; // 0 -> unsort, 1 -> sort
        sort_result *s_results;

        int *array2 = copy_array(array, len); //origin array cannot be sorted

        //printf("Before: ");
        //show_array(array, len);

        if (clock_gettime(CLOCK_MONOTONIC, &start_t) == -1) exit(0);
        s_results = sort_functions(array2, len);
        if (clock_gettime(CLOCK_MONOTONIC, &end_t) == -1) exit(0);
        total_t = ((double) end_t.tv_sec + 1.0e-9 * (double) end_t.tv_nsec) -
                  ((double) start_t.tv_sec + 1.0e-9 * (double) start_t.tv_nsec);

        //printf("After: ");
        //show_array(array2, len);

        //printf("Index = %d is done Time = %.7f Count = %lli \n", p_results->index, total_t, sort_result.count);

        // verify array is sorted
        is_sorted = verify(s_results->sorted_array, len);
        if (!is_sorted) {
            printf("Index = %d Is not sorted\n", len);
        }

        //record p_results
        p_results->array[p_results->index] = (int *)malloc(len * sizeof(int));
        for(int i = 0; i < len; i++){
            p_results->array[p_results->index][i] = array[i];
        }
        p_results->basic_operation_array[p_results->index] = s_results->count;
        p_results->index++;
    } else {
        for(int i = index; i < len; i++){
            swap(array, index, i);
            permutation_test(array, index + 1, len, sort_functions, p_results);
            swap(array, index, i); // backtrack
        }
    }

    return *p_results;
}