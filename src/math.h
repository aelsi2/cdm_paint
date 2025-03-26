#pragma once

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define abs(a) ((a) < 0 ? -(a) : (a))
#define sign(a) ((a) < 0 ? -1 : (a) > 0)

extern int multiply(int a, int b);