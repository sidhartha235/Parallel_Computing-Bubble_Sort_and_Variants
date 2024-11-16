#ifndef INOUT_HEADER
#define INOUT_HEADER

#define MAX_NUMS   1000000
#define MAX_CHARS  1000000000

FILE* openFile(char* filename, char* mode);
void closeFile(FILE* fp);
int read_input(char* filename, int* data);
int generate_input(char* filename, int count);
int write_output(char* filename, int* data, int count);
int write_result(char* filename, char* algorithm, int data_count, int thread_count, double execution_time);

#endif
