#include "functions.h"

int main(int argc, char const *argv[]){
    bool exercise1 = false;
    bool exercise2 = false;
    bool exercise3a = true;
    bool exercise3b = false;
    bool exercise3c = false;


    if (exercise1){
        double x = 3.0;
        int n = 10;
        double *a = (double *)malloc(n * sizeof(double));
        double *b = (double *)malloc(n * sizeof(double));



        // a)
        /*
        for (i=0; i < (int) sqrt(x); i++){
            a[i] = 2.3 * x;
            if (i < 10) b[i] = a[i];
        }
        */
        // some obfuscating declarations here, but this is very simple.
        #pragma omp parallel for
        for (int i = 0; i < (int) sqrt(x); i++){
            a[i] = 2.3 * x;
            if (i < 10) b[i] = a[i];
        }



        // b)
        /*
        flag = 0;
        for (i = 0; (i<n) & (!flag); i++){
            a[i] = 2.3 * i;
            if (a[i] < b[i]) flag = 1;
        }
        Here the loop terminates the first time a[i] < b[i]. If we parallelize
        this loop, the values in a might be different when we exit the loop vs
        the serial case. When using openMP this will not compile due to the
        condition in the for loop. But even if we could, the results would
        change depending on how the iterations are scheduled.
        */



        // c)
        /*
        for (i = 0; i < n; i++){
            a[i] = foo(i);
        }
        If we assume no black magic going on in the function foo(). Then it’s
        rather trivial to parallelize.
        */
        #pragma omp parallel for
        for (int i = 0; i < n; i++){
            a[i] = foo(i);  // this foo function needs to be changed
        }



        // d)
        /*
        for (i = 0; i < n; i++){
            a[i] = foo(i);
            if (a[i] < b[i]) a[i] = b[i];
        }
        There is still no dependence between the different entries in a.
        */
        #pragma omp parallel for
        for (int i = 0; i < n; i++){
            a[i] = foo(i);
            if (a[i] < b[i]) a[i] = b[i];
        }



        // e)
        /*
        for (i = 0; i < n; i++){
            a[i] = foo(i);
            if (a[i] < b[i]) break;
        }
        Here the contents of a after exiting the loop depends on the order we
        iterate over a. If we parallelize we get a race condition. Not suitable
        for parallelization.
        */



        // f)
        /*
        dotp = 0;
        for (i = 0; i < n; i++){
            dotp += a[i] * b[i];
        }
        In this case each iteration of the loop loads values that does not
        depend on the iteration before it. But all the iterations write to the
        same variable. This is what we call a reduction operation. To
        parallelize this we tell openMP that dotp is a reduction variable, and
        that we want the sum total.
        */
        int dotp = 0;
        #pragma omp parallel for reduction(+ : dotp)
        for (int i = 0; i < n; i++){
            dotp += a[i] * b[i];
        }
        /*
        When the loop is exited and the threads synchronized, dotp will have
        the correct value. There are a few reduction operations, see section
        2.14.3.6 in the openMP API.
        */



        // g)
        /*
        for (i = k; i < 2*k; i++){
            a[i] = a[i] + a[i-k];
        }
        Here a[i] depends on a value earlier in the array. Often this means
        that there is limited potential for parallelization, but the index i-k
        is outside the area we are writing to for every iteration (we start
        with i=k). So there is no race condition.
        */
        int k = 8;
        #pragma omp parallel for
        for (int i = k; i < 2*k; i++){
            a[i] = a[i] + a[i-k];
        }



        // h)
        /*
        for (i = k; i < n; i++){
            a[i] = b * a[i-k];
        }
        Here we can not be certain that we are writing to elements not changed
        inside the loop body. There is a potential for a race condition, and
        without knowing the values of k and n we can not be certain.
        If n ≤ 2k we are in the same situation as in g), and we can parallelize.
        It is possible to parallelize this even when n > 2k, but it takes some
        effort. See section 6.3 in the book if you are interested.
        */
    }

    if (exercise2){
        /*
        Inner product is the same as a dot product and the code for this is
        given in ex. 1, f). We only have to change the type of openMP scheduler
        we are using. There are several types:
        - static
        - dynamic
        - guided
        - auto
        - runtime
        You can read about what the different methods do in the openMP API, in
        section 2.7.1.

        Adding the `schedule` directive to our pragma:
        int dotp = 0;
        #pragma omp parallel for reduction(+ : dotp) schedule(schedule_type, chunk_size)
        for (int i = 0; i < n; i++){
            dotp += a[i] * b[i];
        }

        The openMP library comes with a timer function that is very easy to
        use, and is useful now that we are moving to programs with multiple
        threads executing concurrently.

        double start = omp_get_wtime();
        // Do some parallel work here
        double end = omp_get_wtime();
        double total = end - start;

        This function returns the current time in seconds since a reference
        time.
        */




        // actual program they have made;
        int n = 100000000;
        int chunk_size = 100;

        printf("n = %d\n", n);
        printf("chunk_size = %d\n", chunk_size);

        double *a = malloc(n * sizeof *a);
        double *b = malloc(n * sizeof *b);

        double factor = 1./n;
        for (size_t i = 0; i < n; i++) {
            a[i] = i*factor;
            b[i] = i*factor;
        }

        double dotp = 0;

        // Without openMP:
        double start = omp_get_wtime();
        for (size_t i = 0; i < n; i++)
            dotp += a[i] * b[i];
        double end = omp_get_wtime();
        double tot_s = end - start; // Total serial time.
        printf("Time no omp:  %lf\n", tot_s);

        // Using the default scheduler:
        start = omp_get_wtime();
        #pragma omp parallel for reduction(+ : dotp)
        for (size_t i = 0; i < n; i++)
            dotp += a[i] * b[i];
        end = omp_get_wtime();
        double tot = end - start;
        printf("Time default: %lf, ", tot);
        printf("Speedup: %.2lf\n", tot_s/tot);

        // Using static scheduler:
        start = omp_get_wtime();
        #pragma omp parallel for reduction(+ : dotp) schedule(static, chunk_size)
        for (size_t i = 0; i < n; i++)
            dotp += a[i] * b[i];
        end = omp_get_wtime();
        tot = end - start;
        printf("Time static:  %lf, ", tot);
        printf("Speedup: %.2lf\n", tot_s/tot);

        // Using guided scheduler:
        start = omp_get_wtime();
        // You can add chunk size to the guided schedule, it acts as a minimum.
        #pragma omp parallel for reduction(+ : dotp) schedule(guided)
        for (size_t i = 0; i < n; i++)
            dotp += a[i] * b[i];
        end = omp_get_wtime();
        tot = end - start;
        printf("Time guided:  %lf, ", end - start);
        printf("Speedup: %.2lf\n", tot_s/tot);


        // Using auto scheduler:
        start = omp_get_wtime();
        #pragma omp parallel for reduction(+ : dotp) schedule(auto)
        for (size_t i = 0; i < n; i++)
            dotp += a[i] * b[i];
        end = omp_get_wtime();
        tot = end - start;
        printf("Time auto:    %lf, ", end - start);
        printf("Speedup: %.2lf\n", tot_s/tot);

        free(a);
        free(b);
    }

    if (exercise3a){
        /*
        One thing to note before we start. In this function `A` is not a
        pointer to pointer. We are instead using `i*n + j` as the index to
        access the elements in the right order.
        */

        // a) serial version
        /*
        The different versions of the matrix-vector multiplication functions
        are put in its own header file, `matvec.h`, this week. Review the
        source code for a solution. Notice that there is an a index function
        defined near the top that is used when assigning values to `A`.

        #define idx(i,j) (i*n + j)

        Wherever the preprocessor finds an expression `idx(i,j)`, it is
        replaced with `(i*n + j)` before compilation.
        */

        // program they made
        if (argc < 3) {
            printf("Must provide m and n.\n");
            return 1;
        }
        int m = atoi(argv[1]);
        int n = atoi(argv[2]);

        double *A = malloc(m*n*sizeof *A); // m*n matrix
        double *y = malloc(n * sizeof *y); // n*1 vector
        double *x = malloc(m * sizeof *x); // m*1 vector

        // Assign some values
        for (size_t i = 0; i < m; i++) {
            for (size_t j = 0; j < n; j++) {
                A[idx(i,j)] = i + j;
            }
        }

        for (size_t j = 0; j < n; j++) {
            y[j] = j;
        }

        dense_mat_vec(m, n, x, A, y);

        // Print result
        if (m <= 10) {
            printf("x=\n[");
            for (size_t i = 0; i < m-1; i++) {
                printf("%.0lf, ", x[i]);
            }
            printf("%.0lf]\n", x[m-1]);
        }

        free(A);
        free(y);
        free(x);
    }

    if (exercise3b){
        // b) OpenMP parallel version
        /*
        see dense_mat_vec_omp-function to see what was done in b)!
        */

        // program they made
        if (argc < 3) {
            printf("Must provide m and n.\n");
            return 1;
        }
        int m = atoi(argv[1]);
        int n = atoi(argv[2]);

        double *A = malloc(m*n*sizeof *A); // m*n matrix
        double *y = malloc(n * sizeof *y); // n*1 vector
        double *x = malloc(m * sizeof *x); // m*1 vector

        // Assign some values in parallel
        #pragma omp parallel for
        for (size_t i = 0; i < m; i++) {
            for (size_t j = 0; j < n; j++) {
                A[idx(i,j)] = i + j;
            }
        }

        #pragma omp parallel for
        for (size_t j = 0; j < n; j++) {
            y[j] = j;
        }

        double start_s = omp_get_wtime();
        dense_mat_vec(m, n, x, A, y);
        double end_s = omp_get_wtime();
        double tot_s = end_s - start_s;

        double start_p = omp_get_wtime();
        dense_mat_vec_omp(m, n, x, A, y);
        double end_p = omp_get_wtime();
        double tot_p = end_p - start_p;

        // Print result
        if (m <= 20) {
            printf("x=\n[");
            for (size_t i = 0; i < m-1; i++) {
                printf("%.0lf, ", x[i]);
            }
            printf("%.0lf]\n", x[m-1]);
        }

        printf("Time serial:   %lf\n", tot_s);
        printf("Time parallel: %lf\n", tot_p);
        printf("Speedup: %lf\n", tot_s/tot_p);

        free(A);
        free(y);
        free(x);
    }

    if (exercise3c){
        // c) constraints
        /*
        For an arbitrary function this task is impossible, but in this specific
        case we can find a way to decompose the problem. Last week we worked on
        block decomposition. We can use the same technique here to divide the
        matrix $A$, and vector $x$, in to parts that each thread can call
        `dense_mat_vec()` on.
        ´´´
        #pragma omp parallel
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        // Using integer division to divide up the rows means that the last
        // remainder = m%num_threads, gets an extra row.
        int start_m = (thread_id*m)/num_threads;
        int stop_m = ((thread_id+1) * m)/num_threads;

        // calls the serial dense_mat_vec function
        dense_mat_vec(stop_m-start_m, n, &x[start_m], &A[start_m*n], y);
        ´´´
        Notice that we are only decomposing `A` and `x`. We want each element
        in `x` to be written to by only one thread to minimize false sharing.
        False sharing is when multiple threads try to write to the same cache
        line. When an element in a cache line is updated, the line is marked as
        modified, forcing the other threads to reload the line before their own
        write operations can be completed. See section 4.2.1 in the book. This
        takes memory bandwidth, and there is also a latency incurred every
        time.
        */

        if (argc < 3) {
            printf("Must provide m and n.\n");
            return 1;
        }
        int m = atoi(argv[1]);
        int n = atoi(argv[2]);

        double *A = malloc(m*n*sizeof *A); // m*n matrix
        double *y = malloc(n * sizeof *y); // n*1 vector
        double *x = malloc(m * sizeof *x); // m*1 vector

        // Assign some values in parallel
        #pragma omp parallel for
        for (size_t i = 0; i < m; i++) {
            for (size_t j = 0; j < n; j++) {
                A[idx(i,j)] = i + j;
            }
        }

        #pragma omp parallel for
        for (size_t j = 0; j < n; j++) {
            y[j] = j;
        }

        double start_p = omp_get_wtime();
        #pragma omp parallel
        {
          int thread_id = omp_get_thread_num();
          int num_threads = omp_get_num_threads();

          // Using integer division to divide up the rows means that the last
          // remainder = m%num_threads, gets an extra row.
          int start_m = (thread_id*m)/num_threads;
          int stop_m = ((thread_id+1)*m)/num_threads;

          // calls the serial dense_mat_vec function
          dense_mat_vec(stop_m-start_m, n, &x[start_m], &A[start_m*n], y);
        }
        double end_p = omp_get_wtime();
        double tot_p = end_p - start_p;

        // Print result
        if (m <= 20) {
            printf("x=\n[");
            for (size_t i = 0; i < m-1; i++) {
                printf("%.0lf, ", x[i]);
            }
            printf("%.0lf]\n", x[m-1]);
        }

        double start_s = omp_get_wtime();
        dense_mat_vec(m, n, x, A, y);
        double end_s = omp_get_wtime();
        double tot_s = end_s - start_s;

        // Print result for comparison
        if (m <= 20) {
            printf("x=\n[");
            for (size_t i = 0; i < m-1; i++) {
                printf("%.0lf, ", x[i]);
            }
            printf("%.0lf]\n", x[m-1]);
        }

        printf("Time serial:   %lf\n", tot_s);
        printf("Time parallel: %lf\n", tot_p);
        printf("Speedup: %lf\n", tot_s/tot_p);

        free(A);
        free(y);
        free(x);
    }
}
