#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>

bool has_request[10005];
std::vector<std::vector<int>> before(10005);
int target[10005];
int now[10005];
std::vector<int> res;
int ans;

void dfs(int cur) {
    
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
        // std::cout << "*" << test_print++ << '\n';
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
            for (int k = 0; k < idx; k++) {
                for (int i = idx - 1; i >= 0; i--) {
                    int ti = i;
                    if (has_request[now[i]]) {
                        for (int j = i - 1; j >= 0; j--) {
                            for (auto val: before[now[ti]]) {
                                if (now[j] == val) {
                                    std::swap(now[ti], now[j]);
                                    ti = j;
                                }
                            }
                        }
                    }
                }
            }
            //std::reverse(res.begin(), res.end());
            ans += now[idx/2];
            for (int i = 0; i < idx; i++) {
                std::cout << now[i];
                std::cout << " ";
            }
            putchar('\n');
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
