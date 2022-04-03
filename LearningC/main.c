#include <stdio.h>
#include <float.h>

/* declaration of function */
void func_1(int);
int *getMax(int *m, int *n);

/* global variable declaration */
int g;

int main(int argc, char *argv[]){
    /* my first program in C */
    printf("Hello, World! \n");
    /* sizeof yields the storage size of the object or type in
     * number of bytes */
    printf("Storage size for int : %d \n", sizeof(int));
    printf("Minimum float positive value: %E\n", FLT_MIN);
    printf("Maximum float positive value: %E\n", FLT_MAX);
    printf("Precision value: %d\n", FLT_DIG);


    /* calling function */
    int x = 10;
    printf("Before function call\n");
    printf("x = %d\n", x);
    func_1(x);
    printf("After function call\n");
    printf("x = %d\n", x);


    /* local variable declaration */
    int a, b;
    /* actual initialization */
    a = 10;
    b = 20;
    g = a + b;
    printf("value of a = %d, b = %d and g = %d\n", a, b, g);


    /* access an address in memory with ampersand (&) */
    int var1;
    char var2[10];
    printf("Address of var1 variable: %x\n", &var1);
    printf("Address of var2 variable: %x\n", &var2);


    /* a pointer is a variable whose value is the address of
     * another variable */
    /* pointer variable declaration */
    // int *ip;        // pointer to an integer
    // double *dp;     // pointer to a double
    // float *fp;      // pointer to a float
    // char *ch;       // pointer to a character
    int var = 20;      // actual variable declaration
    int *ip;           // pointer variable declaration
    ip = &var;         // store address of var in pointer variable
    printf("Address of var variable: %x\n", &var);
    /* address stored in pointer variable */
    printf("Address stored in ip variable: %x\n", ip);
    /* access the value using the pointer */
    printf("Value of *ip variable: %d\n", *ip);
    /* you can have a pointer on a pointer and so on */


    /* you can return a pointer in a function, but be very
     * careful with such usage */
    int x = 100;
    int y = 200;
    int *max = NULL;
    /* get the variable address that holds the greater value
     * for this we are passing the address of x and y
     * to the function getMax() */
    max = getMax(&x, &y);
    printf("Max value: %d\n", *max);


    /* defining a structure (allows to combine data items of different kinds) */
    /*
    struct Books{
        char title[50];
        char author[50];
        char subject[100];
        int book_id;
    } book;
    */


    /* C provides several functions for memory allocation and management */
    // void *calloc(int num, int size);             // allocates an array of num elements each of which size in bytes will be size, initializes with zero
    // void free(void *address);                    // releases a block of memory specified by address
    // void *malloc(int num);                       // allocates an array of num bytes and leave them uninitialized
    // void *realloc(void *address, int newsize);   // re-allocates memory extending it upto newsize
    /* example of dynamic memory allocation */
    int n, i, *ptr, sum = 0;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    ptr = (int*) malloc(n * sizeof(int));
    if(ptr == NULL){
        printf("Error! memory not allocated."); exit(-1);
    }
    printf("Enter elements: ");
    for(i = 0; i < n; ++i){
        scanf("%d", &(ptr[i]));
        sum += ptr[i];
    }
    printf("Sum = %d\n", sum);
    free(ptr);


    /* input arguments to the main function / command line arguments */
    if(argc == 2){
        printf("The argument supplied is %s\n", argv[1]);
    }
    else if(argc > 2){
        printf("Too many arguments supplied.\n");
    }
    else{
        printf("One argument expected.\n");
    }


    /* simple I/O (Input/Output) */
    FILE *fopen(const char *filename, const char *mode); // opening a file
    int fclose(FILE *fp);                                // closing a file
    /* writing to a file (many different functions available) */
    /* reading to a file (many different functions available) */
    /* binary I/O functions: */
    size_t fread(void *ptr, size_t size_of_elements, size_t number_of_elements, FILE *a_file);
    size_t fwrite(const void *ptr, size_t size_of_elements, size_t number_of_elements, FILE *a_file);


    return 0;
}

/* definition of function */
void func_1(int a){
    /* body of function */
    a += 1;
    a++;
    printf("\na = %d\n\n", a);
}

int *getMax(int *m, int *n){
    /* if the value pointed by pointer m is greater than n
     * then, return the address stored in the pointer variable m */
    if (*m > *n){
        return m;
    }
    else{
        return n;
    }
}
