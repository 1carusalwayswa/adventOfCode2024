#include <iostream>
#include <algorithm>

long long a[10005];
long long b[10005];
int vis[100005];

int main() {
    int a_idx, b_idx;
    a_idx = b_idx = 0;
    while(std::cin>> a[a_idx++] >> b[b_idx++]) {}
    // std::sort(a, a + a_idx);
    // std::sort(b, b + b_idx);

    for (int i = 0;i < a_idx;i++) {
        vis[b[i]]++;
    }

    long long ans = 0;
    for (int i = 0;i < a_idx;i++) {
        ans += a[i] * vis[a[i]];
    }

    printf("%lld", ans);

    return 0;
}