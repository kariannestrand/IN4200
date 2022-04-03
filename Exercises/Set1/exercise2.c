
void ex2a(){
    temperature_data *data;
    data = (temperature_data *)malloc(sizeof(temperature_data));



    /* reading file */
    int err;
    FILE *datafile;
    char filename[] = "temp.txt";
    datafile = fopen(filename, "r");
    if (datafile == NULL){
        printf("Failed to open file %s\n", filename);
        exit(0);
    }
    err = fscanf(datafile, "%d", &data->n);                     // don't know what this is, but without it everything is zero???
    printf("err: %d \n", err);
    printf("Data struct: %d \n", data->n);                      // this reads the first line, number is assigned to n (number of lines in txt-file)
    data->times = (char *)malloc(5 * data->n * sizeof(char));   // 5 specifies amount of characters in time-elements
    data->temps = (double *)malloc(data->n * sizeof(double));
    for (int i = 0; i < data->n; i ++){
        err = fscanf(datafile, "%5s %lf", &data->times[5 * i], &data->temps[i]);  // 5s = 5 characters in a string, lf = long integer
    }
    fclose(datafile);



    /* minimum */
    int minidx;
    double min;
    minidx = 0;
    min = data->temps[0];
    for (int i = 0; i < data->n; i ++) {
        minidx = MINIDX(minidx, i, data->temps);
    }



    /* maximum */
    int maxidx;
    double max;
    maxidx = 0;
    max = data->temps[0];
    for (int i = 0; i < data->n; i ++) {
        maxidx = MAXIDX(maxidx, i, data->temps);
    }



    /* average */
    double sum = 0;
    for (int i =0; i < data->n; i ++) sum += data->temps[i];
    double avg = sum / (double)data->n;



    /* standard deviation */
    double dev = 0;
    double term;
    for (int i = 0; i < data->n; i ++) {
        term = data->temps[i] - avg;
        dev += term * term;
    }
    dev = sqrt(dev/(double)(data->n - 1));



    /* print results */
    for (int i = 0; i < data->n; i ++) {
        printf("%.5s %lf\n", &data->times[5 * i], data->temps[i]);
    }
    printf("Lowest temperature  %f at time %.5s\n", data->temps[minidx], &data->times[5 * minidx]);
    printf("Highest temperature  %f at time %.5s\n", data->temps[maxidx], &data->times[5 * maxidx]);
    printf("Mean temperature %f, with standard deviation %f.\n", avg, dev);
    free(data->times);
    free(data->temps);
    free(data);
}


void ex2b(int n, int m, double c){
    /* 2D-array v */
    double **v;
    v = (double **)malloc(n * sizeof(double *));
    v[0] = (double *)malloc(n * m * sizeof(double));
    for (int i = 1; i < n; i++){
        v[i] = &(v[0][m * i]);
    }

    /* 2D-array v_new */
    double **v_new;
    v_new = (double **)malloc(n * sizeof(double *));
    v_new[0] = (double *)malloc(n * m * sizeof(double));
    for (int i = 1; i < n; i++){
        v_new[i] = &(v_new[0][m * i]);
    }

    /* 2D smooth function */
    for (int i = 1; i < n-1; i++){
        for (int j = 1; j < m-1; j++){
            v_new[i][j] = v[i][j] + c * (v[i-1][j] + v[i][j-1] - 4 * v[i][j] + v[i][j+1] + v[i+1][j]);
        }
    }
    v_new[0][0] = v[0][0];
    v_new[n-1][m-1] = v[n-1][m-1];
}
