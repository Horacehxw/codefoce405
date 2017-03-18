#include <cstdio>
#include <cmath>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    double ratio = (double) b / (double) a;
    double x = log(ratio) / log(1.5);
    int n = ((int) x) + 1;
    printf("%d", n);
    return 0;
}
