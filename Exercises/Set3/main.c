#include "main.h"
#include "functions.c"


int main(int argc, char *argv[]){
    bool exercise1 = false;
    bool exercise2 = false;
    bool exercise3 = true;

    if (exercise1){
        double x_min = 0.;
        double x_max = 1.;
        int slices = 10;

        unsigned long long start = __rdtsc(); // starts counting clock cycles

        double value = numerical_integration(x_min, x_max, slices);
        printf("The integration approaches %f \n", value);

        unsigned long long end = __rdtsc();   // ends counting clock cycles

        double avg = (double)(end - start)/slices;
        printf("Average number of cycles: %lf\n", avg);
    }

    if (exercise2){
        /* for-loop computing the dot-product between two arrays */
        /*
        double s = 0.;
        for (int i = 0; i < N; i++){
            s = s + A[i]*B[i];
        }
        */

        // a)
        /*
        Since a cache line holds consecutive elements in memory one cache line
        must be fetched for each array. At this point there will be data in the
        cache to complete four multiplications, and four additions, for a total
        of 8 flops. The total number of bytes on one cache line is 32
        (4 double precision floats). If we divide by the bandwidth we get
        $$\frac{32\text{Bytes}}{3.2\text{GBytes/sec}} = 10\text{ns}$$
        The latency to load one cache line is 100ns. The total for both cache
        lines is then 220ns. Since the flops in this situation is negligible
        compared to the memory management the performance is approximately
        \(8\text{Flops}/220\text{ns} = 36\text{MFlops/sec}\)
        */

        // b)
        /*
        From **a)** we know that the time used to load one cache line is 10ns.
        Using eq. 1.6 from the textbook we then get
        $$P = 1 + \frac{100\text{ns}}{10\text{ns}} = 11$$
        A total of 11 outstanding prefetches are necessary.
        */

        // c)
        /*
        For line lengths two and four times as long, the transfer time without
        latency is 20ns and 40ns respectively.
        Inserting this into eq. 1.6 we get
        $$P_2 = 1 + \frac{100\text{ns}}{20\text{ns}} = 6$$
        $$P_4 = 1 + \frac{100\text{ns}}{40\text{ns}} = 3.5$$
        Of course we can't do half of a prefetch so \(P_4 = 4\).
        */

        // d)
        /*
        Without latency we can load two cache lines in 20ns. With the assumed
        performance of our CPU the 8 flops take less than this.
        The total time is then
        $$\frac{8\text{Flops}}{20\text{ns}} = 400\text{MFlops/sec}$$
        */
    }

    if (exercise3){
        clock_t standard_start = clock();
        double standard = pow(4, 100);
        clock_t standard_end = clock();
        double standard_time = (standard_end - standard_start);

        clock_t special_start = clock();
        double special = pow100(4);
        clock_t special_end = clock();
        double special_time = (special_end - special_start);


        printf("Time used by standard implementation of 4^100: %f \n", standard_time);
        printf("Time used by special implementation of 4^100: %f \n", special_time);
        printf("Speedup: %lf \n", standard_time/special_time);
    }

    return 0;
}
