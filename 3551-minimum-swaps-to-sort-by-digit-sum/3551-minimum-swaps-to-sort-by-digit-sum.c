#include <stdlib.h>

int digitSum(int x){
    int s=0;
    while(x>0){ s+=x%10; x/=10; }
    return s;
}

typedef struct{
    int val;
    int dsum;
    int idx;
} Node;

int cmpNode(const void*a,const void*b){
    Node *na=(Node*)a, *nb=(Node*)b;
    if(na->dsum != nb->dsum) return na->dsum - nb->dsum;
    return na->val - nb->val;
}

int minSwaps(int* nums, int numsSize){
    int n=numsSize;
    Node *arr=(Node*)malloc(n*sizeof(Node));
    for(int i=0;i<n;i++){
        arr[i].val=nums[i];
        arr[i].dsum=digitSum(nums[i]);
        arr[i].idx=i;
    }
    qsort(arr,n,sizeof(Node),cmpNode);

    // P[original_idx] = target_pos
    int *P=(int*)malloc(n*sizeof(int));
    for(int target=0; target<n; target++){
        int orig = arr[target].idx;
        P[orig]=target;
    }

    int *vis=(int*)calloc(n,sizeof(int));
    int swaps=0;
    for(int i=0;i<n;i++){
        if(vis[i] || P[i]==i) continue;
        int cycle=0, j=i;
        while(!vis[j]){
            vis[j]=1;
            j=P[j];
            cycle++;
        }
        if(cycle>0) swaps += (cycle-1);
    }
    free(arr); free(P); free(vis);
    return swaps;
}

// LeetCode function name change kar sakte hain
// Kuch versions me function name ye hai:
int minimumSwaps(int* nums, int numsSize){
    return minSwaps(nums, numsSize);
}