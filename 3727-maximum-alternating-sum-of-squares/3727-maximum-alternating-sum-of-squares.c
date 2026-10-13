#include <stdlib.h>

int cmp(const void* a, const void* b) {
    long long x = llabs((long long)(*(int*)a));
    long long y = llabs((long long)(*(int*)b));
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

long long maxAlternatingSumOfSquares(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), cmp);

    long long ans = 0;
    int minusCount = numsSize / 2; 

    for (int i = 0; i < numsSize; i++) {
        long long sq = (long long)nums[i] * nums[i];
        if (i < minusCount)
            ans -= sq;
        else
            ans += sq;
    }
    return ans;
}

long long maxAlternatingSum(int* nums, int numsSize){
    return maxAlternatingSumOfSquares(nums, numsSize);
}