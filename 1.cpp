#include <iostream>
#include <algorithm>

int a[10005];
int b[10005];

int main() {
    int a_idx, b_idx;
    a_idx = b_idx = 0;
    while(std::cin>> a[a_idx++] >> b[b_idx++]) {}
    std::sort(a, a + a_idx);
    std::sort(b, b + b_idx);

    long long ans = 0;
    for (int i = 0;i < a_idx;i++) {
        ans += abs(a[i] - b[i]);
    }

    printf("%lld", ans);

    return 0;
}