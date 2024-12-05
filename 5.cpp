#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>

bool has_request[10005];
std::vector<std::vector<int>> before(10005);
int target[10005];
int now[10005];
int tmp_num[1005];
int ans = 0;
int vis[10005];

void dfs(int cur, int end) {
    if (cur == end) {
        memset(target, 0, sizeof(target));
        int flag = true;
        for (int i = 0; i < end; i++) {
            if (has_request[tmp_num[i]]) {
                for (auto val : before[tmp_num[i]]) {
                    if (target[val]) {
                        flag = false;
                        break;
                    }
                }
                if (!flag) break;
            }
            target[tmp_num[i]] = 1;
        }
        if(flag) ans += tmp_num[end / 2]; 
    }

    for (int i = 0; i < end; i++) {
        if (!vis[now[i]]) {
            vis[now[i]] = 1;
            tmp_num[cur] = now[i];
            dfs(cur + 1, end);
            vis[now[i]] = 0;
        }
    }
}

int main() {
    freopen("/Users/lyon/Desktop/TDDD38/adventOfCode2024/5_input.txt", "r", stdin);

    int a, b;
    while(scanf("%d|%d", &a, &b) == 2) {
        before[a].push_back(b);
        has_request[a] = true;
    }

    
    std::string tmp_str{};
    int first_time = 1;
    int test_print = 0;
    while(std::getline(std::cin, tmp_str)) {
        std::cout << "*" << test_print++ << '\n';
        int idx = 0;

        if (first_time) {
            now[idx++] = a;
            first_time = 0;
            tmp_str = tmp_str.substr(1, tmp_str.size() - 1);
        }
        
        std::stringstream ss(tmp_str);
        std::string cur_num {};

        while(std::getline(ss, cur_num, ',')) {
            now[idx++] = std::stoi(cur_num);
        }

        memset(target, 0, sizeof(target));
        int flag = true;
        for (int i = 0; i < idx; i++) {
            if (has_request[now[i]]) {
                for (auto val : before[now[i]]) {
                    if (target[val]) {
                        flag = false;
                        break;
                    }
                }
                if (!flag) break;
            }
            target[now[i]] = 1;
        }

        if (!flag) {
            dfs(0, idx);
        }

        // if (flag) {
        //     ans += now[idx / 2];
        //     for (int i = 0; i < idx; i++) {
        //         std::cout << now[i];
        //         std::cout << " ";
        //     }
        //     putchar('\n');
        // }
    }

    printf("%d", ans);

    return 0;
}
