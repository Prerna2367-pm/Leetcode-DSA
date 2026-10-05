int myAtoi(char* s) {
    int i = 0;
    int n = strlen(s);

    // 1. whitespace ignore
    while(i < n && s[i] == ' ') i++;

    // 2. sign
    int sign = 1;
    if(i < n && (s[i] == '+' || s[i] == '-')) {
        if(s[i] == '-') sign = -1;
        i++;
    }

    long result = 0;
    // 3. conversion
    while(i < n && s[i] >= '0' && s[i] <= '9') {
        int digit = s[i] - '0';
        result = result * 10 + digit;

        // 4. rounding / overflow clamp
        if(sign == 1 && result > INT_MAX) return INT_MAX;
        if(sign == -1 && -result < INT_MIN) return INT_MIN;
        i++;
    }

    return (int)(result * sign);
}