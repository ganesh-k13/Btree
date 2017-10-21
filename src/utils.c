#include "../include/utils.h"

// Computes time taken given the starting and ending times
double accum_time(struct timespec requestStart, struct timespec requestEnd) {
    
    return ((requestEnd.tv_sec - requestStart.tv_sec)) * 1000 +
            (( requestEnd.tv_nsec - requestStart.tv_nsec ) / MILLION);
}
