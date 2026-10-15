int sumCounts(int* nums, int numsSize) {
    int total = 0;

    for (int i = 0; i < numsSize; i++) {
        int freq[101] = {0}; // nums[i] 1 to 100
        int distinct = 0;

        for (int j = i; j < numsSize; j++) {
            if (freq[nums[j]] == 0) {
                distinct++;
            }
            freq[nums[j]]++;

            total += distinct * distinct;
        }
    }
    return total;
}