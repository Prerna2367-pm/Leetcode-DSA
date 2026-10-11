int sumOfSquares(int* nums, int numsSize){
    int sum = 0;
    int n = numsSize;
    for(int i=0; i<n; i++){
        if(n % (i+1) == 0){
            sum += nums[i] * nums[i];
        }
    }
    return sum;
}