#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <time.h>

#include "inout.h"

FILE* openFile(char* filename, char* mode)
{
    FILE* fp = fopen(filename, mode);
    if (fp == NULL) {
        perror("fopen");
        exit(2);
    }
    return fp;
}

void closeFile(FILE* fp)
{
    if (fclose(fp) == EOF) {
        perror("fclose");
        exit(2);
    }
}

int read_input (char* filename, int* data)
{
    int count = 0;
    char* line = (char *)malloc(MAX_CHARS * sizeof(char));
    if (line == NULL) {
        perror("malloc");
        return -1;
    }
    FILE* fp = openFile(filename, "r");

    if (fgets(line, MAX_CHARS, fp) != NULL) {
        char* token = strtok(line, ","); /* tokenize input numbers */
        while (token != NULL && count < MAX_NUMS) {
            errno = 0;
            data[count] = (int)strtol(token, NULL, 10);
            if (errno != 0) {
                perror("strtol");
                return -1;
            }
            count += 1;
            token = strtok(NULL, ",");
        }
    }
    else {
        fprintf(stderr, "Error in input file!\n");
        return -1;
    }

    closeFile(fp);
    free(line);

    return count;
}

int generate_input (char* filename, int count) {
    FILE* file = openFile(filename, "w");
    int num, max;

    srand(time(NULL));
    max = 3 * count / 4; /* max value that can be generated */

    for (int i = 0; i < count; i++) {
        num = (rand() % max) + 1;
        if (i != count - 1) {
            fprintf(file, "%d,", num);
        }
        else {
            fprintf(file, "%d\n", num);
        }
    }

    fclose(file);
    return count;
}

int write_output (char* filename, int* data, int count) {
    FILE* file = openFile(filename, "w");

    for (int i = 0; i < count; i++) {
        if (i != count - 1) {
            fprintf(file, "%d,", data[i]);
        }
        else {
            fprintf(file, "%d\n", data[i]);
        }
    }

    fclose(file);
    return count;
}

int write_result (char* filename, char* algorithm, int data_count, int thread_count, double execution_time) {
    FILE* file = openFile(filename, "a");

    if (fseek(file, 0, SEEK_END) == -1) {
        perror("fseek");
        return -1;
    }

    long file_size = ftell(file);
    if (file_size == 0) { /* file is empty */
        fprintf(file, "Algorithm,Data Count,Thread Count,Execution Time (s)\n");
    }

    fprintf(file, "%s,%d,%d,%.10f\n", algorithm, data_count, thread_count, execution_time);

    fclose(file);
    return 0;
}
