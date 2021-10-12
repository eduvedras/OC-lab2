// shell cmd: cc spark.c -o spark; ./spark

#include <errno.h>
#include <stdio.h>
#include <stdlib.h> // exit()
#include <string.h> // memset()
#include <stdint.h>
#include <time.h>

#define CACHE_MIN (4 * 1024) // 4 KB
#define CACHE_MAX (4 * 1024 * 1024) // 4 MB
#define N_REPETITIONS (100)

struct timespec get_elapsed(struct timespec const *start) {
    struct timespec end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    struct timespec temp;
    temp.tv_sec = end.tv_sec - start->tv_sec;
    temp.tv_nsec = end.tv_nsec - start->tv_nsec;

    if (temp.tv_nsec < 0) {
        temp.tv_sec -= 1;
        temp.tv_nsec += 1000000000;
    }

    return temp;
}

int main() {
    uint8_t * array = calloc(CACHE_MAX, sizeof(uint8_t));

    fputs("size\tstride\telapsed(s)\tcycles\n", stdout);

    for (size_t cache_size = CACHE_MIN; cache_size <= CACHE_MAX;
         cache_size = cache_size * 2) {
        fprintf(stderr, "[LOG]: running with array of size %zu KiB\n", cache_size >> 10);
        fflush(stderr);
        for (size_t stride = 1; stride <= cache_size / 2; stride = 2 * stride) {
            size_t limit = cache_size - stride + 1;

            /* warm up the cache */
            for (size_t index = 0; index < limit; index += stride) {
                array[index] = array[index] + 1;
            }

            clock_t const start_cycles = clock();

            struct timespec start_time;
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);

            /* ************************************************************** */
            for (size_t repeat = 0; repeat < N_REPETITIONS * stride; repeat++) {
                for (size_t index = 0; index < limit; index += stride) {
                    array[index] = array[index] + 1;
                }
            }
            /* ************************************************************** */


            clock_t const cycle_count = clock() - start_cycles;
            struct timespec time_diff = get_elapsed(&start_time);

            /******************************************************************
             * Note: You can change the code bellow to calculate more measures
             * as needed.
             *****************************************************************/

            /* Get the number of iterations */
            size_t const n_iterations = N_REPETITIONS * limit;

            /* Output to stdout */
            fprintf(stdout, "%zu\t%zu\t%ld.%ld\t%zu\n", cache_size, stride,
                    time_diff.tv_sec, time_diff.tv_nsec, cycle_count);
        }
    }

    return 0;
}
