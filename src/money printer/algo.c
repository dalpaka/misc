#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#define SMA_SPAN 5

double get_sma(double prices[], int start, int span) {
    double sum = 0.0;
    for (int i = start; i < start + span; i++) {
        sum += prices[i];
    }
    return sum / span;
}

void signals (double prices[], int size) {
    for (int i = SMA_SPAN; i < size; i++) {
        double sma = get_sma(prices, i - SMA_SPAN, SMA_SPAN);
        //TODO: cases
    }
}

int main (void) {
   
}