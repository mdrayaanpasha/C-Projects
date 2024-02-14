#include <stdio.h>

int mean(int var[], int varSize) {
    int var_mean = 0;
    for (int i = 0; i < varSize; i++) {
        var_mean += var[i];
    }
    
    var_mean = var_mean / varSize;
    return var_mean;
}

int mxb(int x[], int y[], int size_x, int size_y) {
    int x_mean = mean(x, size_x);
    int y_mean = mean(y, size_y);
    
    int numerator_x = 0;
    for (int i = 0; i < size_x; i++) {
        numerator_x += x[i] - x_mean;
    }
    
    int numerator_y = 0;
    for (int j = 0; j < size_y; j++) {
        numerator_y += y[j] - y_mean;
    }
    int numerator = numerator_x * numerator_y;
    
    int denominator = numerator_x * numerator_x;
    int m = numerator / denominator;
    
    int c = y_mean - m * x_mean;
    
    int fin_y = m * x_mean + c;
    
    return fin_y;
}

void result(int y[], int fin_y, int y_size) {
    int y_mean = mean(y, y_size);
    int sst = 0;
    for (int i = 0; i < y_size; i++) {
        sst += y[i] - y_mean;
    }
    sst = sst * sst;
    
    int sse = 0;
    for (int k = 0; k < y_size; k++) {
        sse += y[k] - fin_y;
    }
    sse = sse * sse;
    
    float r = 1 - (sst / sse); 
    
    printf("The prediction made: %d is %.2f dependent on the other variable", fin_y, r * 100);
}


