char* longestPalindrome(char* s) {
    int n = strlen(s);
    if(n <= 1) return s;

    int start = 0, maxLen = 1;

    for(int i=0; i<n; i++) {
        // case 1: odd length like "bab" - center i
        int l = i, r = i;
        while(l >= 0 && r < n && s[l] == s[r]) {
            if(r - l + 1 > maxLen) {
                start = l;
                maxLen = r - l + 1;
            }
            l--; r++;
        }
        // case 2: even length like "bb" - center i, i+1
        l = i; r = i+1;
        while(l >= 0 && r < n && s[l] == s[r]) {
            if(r - l + 1 > maxLen) {
                start = l;
                maxLen = r - l + 1;
            }
            l--; r++;
        }
    }

    char* ans = (char*)malloc((maxLen + 1) * sizeof(char));
    strncpy(ans, s + start, maxLen);
    ans[maxLen] = '\0';
    return ans;
}