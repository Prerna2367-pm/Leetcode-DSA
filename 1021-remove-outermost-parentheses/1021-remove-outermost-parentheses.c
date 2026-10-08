#include <string.h>
#include <stdlib.h>

char* removeOuterParentheses(char* s){
    int n = strlen(s);
    char* ans = (char*)malloc(n + 1);
    int j = 0;
    int balance = 0;

    for(int i=0; s[i]; i++){
        if(s[i]=='('){
            if(balance>0){
                ans[j++] = s[i];
            }
            balance++;
        }else{
            balance--;
            if(balance>0){
                ans[j++] = s[i];
            }
        }
    }
    ans[j]='\0';
    return ans;
}