#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "inout.h"
#include "sort.h"

int main (int argc, char** argv)
{
    if (argc != 3 || argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Usage: %s <thread_count> <data_count>\n", argv[0]);
        exit(1);
    }

    int thread_count = atoi(argv[1]);
    int data_count = atoi(argv[2]);

    if (thread_count < 1) {
        fprintf(stderr, "Thread count should be non-negative.\n");
        exit(1);
    }

    if (data_count < 2) {
        fprintf(stderr, "Data count should be at least 2.\n");
        exit(1);
    }

    int* data = (int *)malloc(MAX_NUMS * sizeof(int));
    if (data == NULL) {
        perror("malloc");
        exit(3);
    }

    struct timespec start, end;
    double time_taken = 0;
    int choice = -1;
    int flag = 0;
    char* algorithm = (char *)malloc(200 * sizeof(char));
    if (algorithm == NULL) {
        perror("malloc");
        exit(3);
    }

    char* input_file = "input.csv";
    char* output_file = "output.csv";
    char* results_file = "results.csv";

    if (generate_input(input_file, data_count) == -1) {
        fprintf(stderr, "Error while generating input!\n");
        free(data);
        exit(4);
    }
    // printf("Random input of size %d is generated to file: %s\n", data_count, input_file);

    if ((data_count = read_input(input_file, data)) == -1) {
        fprintf(stderr, "Error while reading input!\n");
        free(data);
        exit(4);
    }
    // printf("Input read from file: %s\n", input_file);

    // printf("Input data:\n");
    // for (int i = 0; i < data_count; i++) {
    //     printf("%d ", data[i]);
    // }
    // printf("\n");

    while (choice != 0) {
        flag = 0;

        printf("Select a sorting algorithm:\n");
        printf("1. Bubble Sort\n");
        printf("2. Odd-Even Transposition Sort\n");
        printf("3. Parallel Odd-Even Transposition Sort\n");
        printf("4. Shell Sort\n");
        printf("5. Parallel Shell Sort - Gradual Halving\n");
        printf("6. Parallel Shell Sort - Hibbard sequence\n");
        printf("Enter your choice (1-6 | '0' to exit): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input! Please enter an integer.\n\n");
            
            while (getchar() != '\n'); /* discard entered invalid input */

            choice = -1;
            continue;
        }

        switch (choice) {
            case 0:
                printf("Exiting program..\n");
                flag = 1;
                break;
            case 1:
                algorithm = "Bubble-Sort";
                thread_count = 1;
                clock_gettime(CLOCK_MONOTONIC, &start);
                bubble_sort(data, data_count);
                clock_gettime(CLOCK_MONOTONIC, &end);
                break;
            case 2:
                algorithm = "Odd-Even-Transposition-Sort";
                thread_count = 1;
                clock_gettime(CLOCK_MONOTONIC, &start);
                odd_even_transposition_sort(data, data_count);
                clock_gettime(CLOCK_MONOTONIC, &end);
                break;
            case 3:
                algorithm = "Parallel-Odd-Even-Transposition-Sort";
                clock_gettime(CLOCK_MONOTONIC, &start);
                omp_odd_even_transposition_sort_02(data, data_count, thread_count);
                clock_gettime(CLOCK_MONOTONIC, &end);
                break;
            case 4:
                algorithm = "Shell-Sort";
                thread_count = 1;
                clock_gettime(CLOCK_MONOTONIC, &start);
                shell_sort(data, data_count);
                clock_gettime(CLOCK_MONOTONIC, &end);
                break;
            case 5:
                algorithm = "Parallel-Shell-Sort-Gradual-Halving";
                clock_gettime(CLOCK_MONOTONIC, &start);
                omp_shell_sort(data, data_count, thread_count);
                clock_gettime(CLOCK_MONOTONIC, &end);
                break;
            case 6:
                algorithm = "Parallel-Shell-Sort-Hibbard-Sequence";
                clock_gettime(CLOCK_MONOTONIC, &start);
                omp_shell_sort_02(data, data_count, thread_count);
                clock_gettime(CLOCK_MONOTONIC, &end);
                break;
            default:
                printf("\nInvalid choice!\n\n");
                flag = 1;
                break;
        }

        if (flag) {
            continue;
        }

        // printf("Sorted data:\n");
        // for (int i = 0; i < data_count; i++) {
        //     printf("%d ", data[i]);
        // }
        // printf("\n");

        printf("\nAlgorithm: %s\n", algorithm);
        time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        printf("Execution time: %.10f (%e) seconds\n\n", time_taken, time_taken);

        if (write_output(output_file, data, data_count) == -1) {
            fprintf(stderr, "Error while writing output!\n");
            free(data);
            exit(4);
        }
        // printf("Output written to file: %s\n", output_file);

        if (write_result(results_file, algorithm, data_count, thread_count, time_taken) == -1) {
            fprintf(stderr, "Error while writing result!\n");
            free(data);
            exit(4);
        }

    }
    
    free(data);

    return 0;
}
