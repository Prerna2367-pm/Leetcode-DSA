#include <string.h>
#include <stdlib.h>

char* map[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

char** ans;
int ansSize;
char* curr;

void backtrack(char* digits, int idx, int n){
    if(idx == n){
        ans[ansSize] = strdup(curr);
        ansSize++;
        return;
    }
    int d = digits[idx] - '0';
    char* letters = map[d];
    for(int i=0; letters[i]; i++){
        curr[idx] = letters[i];
        curr[idx+1] = '\0';
        backtrack(digits, idx+1, n);
    }
}

char** letterCombinations(char* digits, int* returnSize){
    int n = strlen(digits);
    if(n==0){
        *returnSize=0;
        return NULL;
    }

    int total = 1;
    for(int i=0;i<n;i++){
        int d = digits[i]-'0';
        if(d==7 || d==9) total*=4;
        else total*=3;
    }

    ans = (char**)malloc(total * sizeof(char*));
    ansSize = 0;
    curr = (char*)malloc((n+1)*sizeof(char));
    curr[0]='\0';

    backtrack(digits, 0, n);

    *returnSize = ansSize;
    free(curr);
    return ans;
}