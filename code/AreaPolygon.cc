double area(int x[], int y[], int n) {
    double a = 0;
    for(int i = 0; i < n - 1; i++) {
        a = a + 1.0*x[i]*y[i+1] - 1.0*x[i+1]*y[i];
    }
    a = a + 1.0*x[n-1]*y[0] - 1.0*x[0]*y[n-1];
    return a
}
