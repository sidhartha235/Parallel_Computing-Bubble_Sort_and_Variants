#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
    #include <omp.h>
#endif
#include <math.h>

#include "sort.h"

void swap (int* a, int* b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void bubble_sort (int* data, int n) {
    int i, list_length;

    for (list_length = n; list_length >= 2; list_length--) {
        for (i = 0; i< list_length - 1; i++) {
            if (data[i] > data[i + 1]) {
                swap(&data[i], &data[i + 1]);
            }
        }
    }
}

void odd_even_transposition_sort (int* data, int n) {
    int i, phase;

    for (phase = 0; phase < n; phase++) {
        if (phase % 2 == 0) {
            for (i = 1; i < n; i += 2) {
                if (data[i - 1] > data[i]) {
                    swap(&data[i - 1], &data[i]);
                }
            }
        }
        else {
            for (i = 1; i < (n - 1); i += 2) {
                if (data[i] > data[i + 1]) {
                    swap(&data[i], &data[i + 1]);
                }
            }
        }
    }
}

void omp_odd_even_transposition_sort_01 (int* data,int n, int thread_count) {
    int i, phase;

    for (phase = 0; phase < n; phase++) {
        if (phase % 2 == 0) {
#           pragma omp parallel for num_threads(thread_count) \
                default(none) shared(data, n) private(i)
            for (i = 1; i < n; i += 2) {
                if (data[i - 1] > data[i]) {
                    swap(&data[i - 1], &data[i]);
                }
            }
        }
        else {
#           pragma omp parallel for num_threads(thread_count) \
                default(none) shared(data, n) private(i)
            for (i = 1; i < (n - 1); i += 2) {
                if (data[i] > data[i + 1]) {
                    swap(&data[i], &data[i + 1]);
                }
            }
        }
    }
}

void omp_odd_even_transposition_sort_02 (int* data,int n, int thread_count) {
    int i, phase;

#   pragma omp parallel num_threads(thread_count) \
        default(none) shared(data, n) private(i, phase)
    for (phase = 0; phase < n; phase++) {
        if (phase % 2 == 0) {
#           pragma omp for
            for (i = 1; i < n; i += 2) {
                if (data[i - 1] > data[i]) {
                    swap(&data[i - 1], &data[i]);
                }
            }
        }
        else {
#           pragma omp for
            for (i = 1; i < (n - 1); i += 2) {
                if (data[i] > data[i + 1]) {
                    swap(&data[i], &data[i + 1]);
                }
            }
        }
    }
}

void shell_sort (int* data, int n) {
    int m, i, j, k;
    
    for (m = n / 2; m != 0; m /= 2) {
        k = n - m;
        for (j = 0; j < k; j++) {
            for (i = j; i >= 0; i -= m) {
                if (data[i] > data[i + m]) {
                    swap(&data[i], &data[i + m]);
                }
            }
        }
    }
}

void omp_shell_sort (int* data, int n, int thread_count) {
    int m, i, j, key, l;
    
    for (m = n / 2; m != 0; m /= 2) {
#       pragma omp parallel for num_threads(thread_count) \
            default(none) private(i, j, key, l) shared(m, n, data)
        for (j = (n - m); j < n; j++) {
            for (i = j; i >= 0; i -= m) {
                key = data[i];
                l = i + m;
                while (l < n && key > data[l]) {
                    data[l - m] = data[l];
                    l += m;
                }
                data[l - m] = key;
            }
        }
    }
}

void omp_shell_sort_02 (int* data, int n, int thread_count) {
    int m, i, j, key, l;
    
    int k = (int)floor(log(n) / log(2));

    for (m = ((int)pow(2, k) - 1); m > 0; m = ((int)pow(2, --k) - 1)) {
#       pragma omp parallel for num_threads(thread_count) \
            default(none) private(i, j, key, l) shared(m, n, data)
        for (j = (n - m); j < n; j++) {
            for (i = j; i >= 0; i -= m) {
                key = data[i];
                l = i + m;
                while (l < n && key > data[l]) {
                    data[l - m] = data[l];
                    l += m;
                }
                data[l - m] = key;
            }
        }
    }
}
