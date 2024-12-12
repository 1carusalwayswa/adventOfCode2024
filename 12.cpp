#include "./utils.hpp"

vector<string> g;
vector<vector<int>> new_g;
int m,n;
int dx[4] {0, -1, 0, 1};
int dy[4] {1, 0, -1, 0};

struct node {
    int len;
    int cnt;
    int st_row, st_col;
    int ed_row, ed_col;
};

bool is_valid(int x, int y) {
    return x >= 0 && x < m && y >= 0 && y < n;
}

node dfs(int x, int y, char ch, int cnt) {
    node ans {4, 1, 0x3f3f3f3f, 0x3f3f3f3f, -1, -1};
    ans.st_row = min(ans.st_row, x);
    ans.st_col = min(ans.st_col, y);
    ans.ed_row = max(ans.ed_row, x);
    ans.ed_col = max(ans.ed_col, y);

    for (int i = 0;i < 4;i++) {
        int tx = x + dx[i];
        int ty = y + dy[i];
        
        if (tx < 0 || tx >= m) continue;
        if (ty < 0 || ty >= n) continue;
        if (g[tx][ty] == (ch - 'A' + 'a')) {
            ans.len -= 1;
            continue;
        }
        if (g[tx][ty] != ch) {
            continue;
        } 
        ans.len -= 1;

        g[tx][ty] = (ch - 'A' + 'a');
        new_g[tx][ty] = cnt;
        // cout << tx << " " << ty << '\n';
        node tmp = dfs(tx, ty, ch, cnt);
        ans.st_row = min(ans.st_row, tmp.st_row);
        ans.st_col = min(ans.st_col, tmp.st_col);
        ans.ed_row = max(ans.ed_row, tmp.ed_row);
        ans.ed_col = max(ans.ed_col, tmp.ed_col);
        ans.len += tmp.len;
        ans.cnt += tmp.cnt;
    }

    return ans;
}

int cal_point(int st_row, int st_col, int ed_row, int ed_col ,int ch) {

    // find convex points
    int ans = 0;
    for (int i = st_row;i <= ed_row;i++) {
        for (int j = st_col;j <= ed_col;j++) {
            if (new_g[i][j] == ch) {
                if (!is_valid(i - 1, j) || new_g[i - 1][j] != ch) {
                    if (!is_valid(i, j - 1) || new_g[i][j - 1] != ch) {
                        ans += 1;
                    }
                    if (!is_valid(i, j + 1) || new_g[i][j + 1] != ch) {
                        ans += 1;
                    }
                }
                if (!is_valid(i + 1, j) || new_g[i + 1][j] != ch) {
                    if (!is_valid(i, j - 1) || new_g[i][j - 1] != ch) {
                        ans += 1;
                    }
                    if (!is_valid(i, j + 1) || new_g[i][j + 1] != ch) {
                        ans += 1;
                    }
                }
            }
        }
    }
    // cout << ans << '\n';

    // find concave points
    for (int i = st_row;i <= ed_row;i++) {
        for (int j = st_col;j <= ed_col;j++) {
            if (new_g[i][j] != ch) {
                if (is_valid(i - 1, j) && new_g[i - 1][j] == ch) {
                    if (is_valid(i, j - 1) && new_g[i][j - 1] == ch) {
                        if (is_valid(i - 1, j - 1) && new_g[i - 1][j - 1] == ch) {
                            ans += 1;
                        }
                    }

                    if (is_valid(i, j + 1) && new_g[i][j + 1] == ch) {
                        if (is_valid(i - 1, j + 1) && new_g[i - 1][j + 1] == ch) {
                            ans += 1;
                        }
                    }
                }
                if (is_valid(i + 1, j) && new_g[i + 1][j] == ch) {
                    if (is_valid(i, j - 1) && new_g[i][j - 1] == ch) {
                        if (is_valid(i + 1, j - 1) && new_g[i + 1][j - 1] == ch) {
                            ans += 1;
                        }
                    }

                    if (is_valid(i, j + 1) && new_g[i][j + 1] == ch) {
                        if (is_valid(i + 1, j + 1) && new_g[i + 1][j + 1] == ch) {
                            ans += 1;
                        }
                    }
                }
            }
        }
    }
    
    return ans;
}

int main() {
    freopen("/Users/lyon/Desktop/TDDD38/adventOfCode2024/12_input.txt", "r", stdin); 
    g = readMat<char>();
    
    m = g.size();
    n = g[0].length();
    int cnt = 1;
    new_g.resize(m, vector<int>(n, 0));
    long long ans_part1 = 0;
    long long ans_part2 = 0;
    for (int i = 0;i < g.size();i++) {
        for (int j = 0;j < g[0].size();j++) {
            if (g[i][j] >= 'A' && g[i][j] <= 'Z') {
                char ch = g[i][j];
                g[i][j] = g[i][j] - 'A' + 'a';
                new_g[i][j] = cnt;
                node tmp = dfs(i, j, ch, cnt);
                int point = cal_point(tmp.st_row, tmp.st_col, tmp.ed_row, tmp.ed_col, cnt);
                cnt++;
                // int new_len = cal(i, j, g[i][j]);
                cout << "[" << ch <<  "]: " << point << " " << tmp.cnt << " " << i << " " << j << '\n';
                ans_part2 += tmp.cnt * point;
                ans_part1 += tmp.cnt * tmp.len;
            }
        }
    }
    // for (auto val : new_g) {
    //     for (auto v : val) {
    //         cout << v << " ";
    //     }
    //     cout << '\n';
    // }
    std::cout << ans_part1 << '\n';
    std::cout << ans_part2 << '\n';
    return 0;
}