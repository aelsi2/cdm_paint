#pragma once

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define abs(a) ((a) < 0 ? -(a) : (a))
#define sign(a) ((a) < 0 ? -1 : (a) > 0)
#define sort(a, b) do { \
    if (a > b) { \
        a ^= b; \
        b ^= a; \
        a ^= b; \
    } \
} while(0)

inline static int wrap_max(int value, int max) {
    if (value < 0) {
        value += max;
    }
    else if (value >= max) {
        value -= max;
    }
    return value;
}

extern int multiply(int a, int b);
