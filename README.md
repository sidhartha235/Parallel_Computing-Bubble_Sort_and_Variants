# Bubble Sort and its Variants

### Parallel Computing Assignment - November 2024
#### by Sidhartha Ananthula - 21MCME08


## Overview

* This program demonstrates the implementation of Bubble Sort and its variants, including parallel methods using OpenMP.
* It allows for flexible selection between different sorting algorithms based on user input.
* Execution time is recoreded for performance analysis.


## Execution Steps

### Using `make`

1. **Compile the Code:** <br>
    Run the following command:
    ```
    make
    ```
    An executable file `main` will be generated.

2. **Run the Program:** <br>
    Execute the program with the command:
    ```
    ./main <thread_count> <data_count>
    ```
    where <br>
    `<thread_count>`: Number of threads to use for a parallel algorithm. <br>
    `<data_count>`: Size of input - these many integers are randomly generated.

### Without `make`

If `make` is not available, compile manually with the command:
```
gcc -Wall -fopenmp -o main main.c inout.c sort.c -lm
```

Then, follow Step 2 above to execute the program.


## Program Options

Choose an option(1-6) from provided algorithms:
1. Bubble Sort
2. Odd-Even Transposition Sort
3. Parallel Odd-Even Transposition Sort
4. Shell Sort
5. Parallel Shell Sort - Gradual Halving
6. Parallel Shell Sort - Hibbard sequence


## Output

* Execution Time (in seconds) is displayed on the terminal.
* Sorted data for the random input(`input.csv`) is saved in a file named `output.csv`.
* Result including the Algorithm, Data Count, Thread Count, and Execution Time (in seconds) is saved to a file `results.csv`. And can be used for Analysis of these algorithms.

***
**NOTE:** The `processed_results.csv` file provided is processed from many runs. To check the unprocessed `results.csv` file visit: [GitHub Repo](https://github.com/sidhartha235/Parallel_Computing-Bubble_Sort_and_Variants.git)