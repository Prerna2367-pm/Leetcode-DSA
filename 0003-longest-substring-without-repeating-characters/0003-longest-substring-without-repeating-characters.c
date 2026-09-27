int lengthOfLongestSubstring(char* s) {
    int lastIndex[256];
    for(int i=0; i<256; i++) lastIndex[i] = -1;

    int maxLen = 0;
    int start = 0;

    for(int end=0; s[end]!='\0'; end++) {
        unsigned char c = s[end];

        if(lastIndex[c] >= start) {
            start = lastIndex[c] + 1;
        }
        lastIndex[c] = end;

        int currLen = end - start + 1;
        if(currLen > maxLen) {
            maxLen = currLen;
        }
    }
    return maxLen;
}