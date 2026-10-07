#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char** ans;
int ansSize, ansCap;
char* path;
bool* seenDup;

bool isValid(char* s){
    int bal=0;
    for(int i=0;s[i];i++){
        if(s[i]=='(') bal++;
        else if(s[i]==')'){
            if(bal==0) return false;
            bal--;
        }
    }
    return bal==0;
}

void dfs(char* s, int idx, int lRem, int rRem, int open, int pIdx){
    if(lRem==0 && rRem==0){
        // bacha hua string check
        int bal=0;
        for(int i=idx; s[i]; i++){
            if(s[i]=='(') bal++;
            else if(s[i]==')'){
                if(bal==0) return;
                bal--;
            }
        }
        // valid banao
        // pIdx tak path copy karo + bacha hua s
        char* tmp = malloc(strlen(s)+2);
        strncpy(tmp, path, pIdx);
        int t = pIdx;
        for(int i=idx; s[i]; i++){
            if(s[i]!='(' && s[i]!=')' || (s[i]=='(' && open>=0) || s[i]==')'){
                // simple append
                if(s[i]=='(') open++;
                else if(s[i]==')') open--;
                tmp[t++] = s[i];
            }
        }
        tmp[t]='\0';
        if(isValid(tmp)){
            // duplicate check
            for(int i=0;i<ansSize;i++) if(strcmp(ans[i], tmp)==0){ free(tmp); return; }
            if(ansSize>=ansCap){
                ansCap*=2;
                ans = realloc(ans, ansCap*sizeof(char*));
            }
            ans[ansSize++] = tmp;
        }else free(tmp);
        return;
    }

    for(int i=idx; s[i]; i++){
        if(s[i]!='(' && s[i]!=')') continue;
        if(i>idx && s[i]==s[i-1]) continue;

        if(s[i]==')' && rRem>0){
            // isko hatana
            int len = strlen(s);
            char* ns = malloc(len+1);
            strncpy(ns, s, i);
            strcpy(ns+i, s+i+1);
            dfs(ns, i, lRem, rRem-1, open, pIdx);
            free(ns);
        }else if(s[i]=='(' && lRem>0){
            int len = strlen(s);
            char* ns = malloc(len+1);
            strncpy(ns, s, i);
            strcpy(ns+i, s+i+1);
            dfs(ns, i, lRem-1, rRem, open, pIdx);
            free(ns);
        }
        // rakhna
        if(s[i]=='(') open++;
        else if(s[i]==')'){
            if(open==0) continue;
            open--;
        }
        path[pIdx]=s[i];
        // pruning ke liye aage badho
        if(s[i+1]=='\0'){
             dfs(s, i+1, lRem, rRem, open, pIdx+1);
        }
    }
}

// main wrapper - fast wala
char** removeInvalidParentheses(char* s, int* returnSize){
    int lRem=0, rRem=0;
    for(int i=0;s[i];i++){
        if(s[i]=='(') lRem++;
        else if(s[i]==')'){
            if(lRem>0) lRem--;
            else rRem++;
        }
    }

    ansCap = 2048;
    ans = malloc(ansCap*sizeof(char*));
    ansSize=0;
    path = malloc(30);

    // classic backtracking
    int n = strlen(s);
    char* cur = malloc(n+1);
    cur[0]='\0';

    void backtrack(int idx, int l, int r, int bal){
        if(idx==n){
            if(l==0 && r==0 && bal==0){
                // duplicate check
                for(int i=0;i<ansSize;i++) if(strcmp(ans[i], cur)==0) return;
                ans[ansSize++] = strdup(cur);
            }
            return;
        }
        if(n-idx < l+r) return; // pruning

        if(s[idx]=='('){
            if(l>0){
                backtrack(idx+1, l-1, r, bal);
            }
            cur[strlen(cur)+1]='\0';
            int len = strlen(cur);
            cur[len]='(';
            cur[len+1]='\0';
            backtrack(idx+1, l, r, bal+1);
            cur[len]='\0';
        }else if(s[idx]==')'){
            if(r>0){
                backtrack(idx+1, l, r-1, bal);
            }
            if(bal>0){
                int len = strlen(cur);
                cur[len]=')';
                cur[len+1]='\0';
                backtrack(idx+1, l, r, bal-1);
                cur[len]='\0';
            }
        }else{
            int len = strlen(cur);
            cur[len]=s[idx];
            cur[len+1]='\0';
            backtrack(idx+1, l, r, bal);
            cur[len]='\0';
        }
    }

    backtrack(0, lRem, rRem, 0);

    if(ansSize==0){
        ans[0]=strdup("");
        ansSize=1;
    }
    *returnSize = ansSize;
    return ans;
}