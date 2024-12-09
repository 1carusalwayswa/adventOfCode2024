#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::string> g;
int m, n;
bool vis[1005][1005];

bool is_valid(int x, int y) {
    if (x < 0 || y < 0) return false;
    if (x >= m || y >= n) return false;

    return true;
}

void target(std::pair<int, int> p1, std::pair<int, int> p2) {
    int diff_x = p1.first - p2.first;
    int diff_y = p1.second- p2.second;

    vis[p1.first][p1.second] = 1;
    vis[p2.first][p2.second] = 1;
    std::pair<int, int> cur_p;
    cur_p = p1;
    if (is_valid(cur_p.first + diff_x, cur_p.second + diff_y)) {
        // cur_p.first += diff_x;
        // cur_p.second += diff_y;
        vis[cur_p.first][cur_p.second] = true;
    }

    diff_x = -diff_x;
    diff_y = -diff_y;
    cur_p = p2;

    if (is_valid(cur_p.first + diff_x, cur_p.second + diff_y)) {
        // cur_p.first += diff_x;
        // cur_p.second += diff_y;
        vis[cur_p.first][cur_p.second] = true;
    }
}

int main() {
    freopen("/Users/lyon/Desktop/TDDD38/adventOfCode2024/8_input.txt", "r", stdin);
    std::string line_str;
    while(std::getline(std::cin, line_str)) {
        g.push_back(line_str);
        // std::cout << line_str << '\n';
        m++;
    }

    n = g[0].size();
    std::unordered_map<char, std::vector<std::pair<int, int>>> mmap;
    for (int i = 0;i < m;i++) {
        for (int j = 0;j < n;j++) {
            char symbol = g[i][j];
            if (symbol != '.') {
                mmap[symbol].emplace_back(i, j);
            }
        }
    }

    memset(vis, 0, sizeof(vis));
    for (const auto& entry : mmap) {
        char symbol = entry.first;
        const std::vector<std::pair<int, int>>& pos = entry.second;
        for (int i = 0; i < pos.size() - 1; i++) {
            auto p1 = pos[i];
            for (int j = i + 1;j < pos.size();j++) {
                auto p2 = pos[j];
                target(p1, p2);
            }
        } 
    }
    
    int ans = 0;
    for (int i = 0;i < m;i++) {
        for (int j = 0;j < n;j++) {
            if (vis[i][j])ans++;
            if(vis[i][j])std::cout << '#';
            else std::cout << g[i][j];
        }
        std::cout << '\n';
    }

    std::cout << ans << '\n';

    return 0;
}