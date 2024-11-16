#ifndef SORT_HEADER
#define SORT_HEADER

void swap(int* a, int* b);
void bubble_sort (int* data, int count);

void odd_even_transposition_sort(int* data, int count);
void omp_odd_even_transposition_sort_01(int* data,int count, int thread_count);
void omp_odd_even_transposition_sort_02(int* data,int count, int thread_count);

void shell_sort(int* data, int count);
void omp_shell_sort(int* data, int count, int thread_count);
void omp_shell_sort_02(int* data, int count, int thread_count);

#endif
