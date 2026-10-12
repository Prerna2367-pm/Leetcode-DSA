#include <stdlib.h>

int cmp(const void* a, const void* b){
    long long x = *(long long*)a;
    long long y = *(long long*)b;
    if(y > x) return 1;
    if(y < x) return -1;
    return 0;
}

int maxSum(int* nums, int numsSize, int k){
    int cnt[31] = {0};
    for(int i=0;i<numsSize;i++){
        for(int b=0;b<31;b++){
            if(nums[i] & (1<<b)) cnt[b]++;
        }
    }

    long long *newNums = (long long*)calloc(numsSize, sizeof(long long));

    for(int b=0;b<31;b++){
        for(int i=0;i<numsSize;i++){
            if(cnt[b]>0){
                newNums[i] |= (1LL<<b);
                cnt[b]--;
            }
        }
    }

    qsort(newNums, numsSize, sizeof(long long), cmp);

    long long MOD = 1000000007LL;
    long long ans = 0;
    for(int i=0;i<k;i++){
        ans = (ans + (newNums[i]%MOD)*(newNums[i]%MOD)%MOD) % MOD;
    }
    free(newNums);
    return (int)ans;
}