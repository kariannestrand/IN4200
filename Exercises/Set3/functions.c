

double numerical_integration(double x_min, double x_max, int slices){
    double delta_x = (x_max - x_min)/slices;
    double x, sum = 0.0;
    for (int i = 0; i < slices; i++){
        x = x_min + (i + 0.5)*delta_x;
        sum = sum + 4.0/(1.0 + x*x);
    }
    return sum*delta_x;
}


double pow100(double x){
    double x4, x32, xp;
    xp = x*x;  // x^2
    xp *= xp;  // x^4
    x4 = xp;
    xp *= xp;  // x^8
    xp *= xp;  // x^16
    xp *= xp;  // x^32
    x32 = xp;
    xp *= xp;  // x^64

    return (x4*x32*xp); //x^(4+32+64)
}
