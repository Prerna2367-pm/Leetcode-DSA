char* convert(char* s, int numRows) {
    int n = strlen(s);
    if(numRows == 1 || n <= numRows) return s;

    // har row ke liye ek string
    char** rows = (char**)malloc(numRows * sizeof(char*));
    int* lens = (int*)calloc(numRows, sizeof(int));
    for(int i=0; i<numRows; i++) {
        rows[i] = (char*)malloc((n+1) * sizeof(char));
    }

    int currRow = 0;
    int goingDown = 0;

    for(int i=0; i<n; i++) {
        rows[currRow][lens[currRow]++] = s[i];

        if(currRow == 0 || currRow == numRows - 1) goingDown =!goingDown;
        currRow += goingDown? 1 : -1;
    }

    char* ans = (char*)malloc((n+1) * sizeof(char));
    int idx = 0;
    for(int i=0; i<numRows; i++) {
        for(int j=0; j<lens[i]; j++) {
            ans[idx++] = rows[i][j];
        }
        free(rows[i]);
    }
    ans[idx] = '\0';
    free(rows);
    free(lens);
    return ans;
}