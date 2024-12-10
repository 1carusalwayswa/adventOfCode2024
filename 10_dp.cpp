#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using std::cin;
using std::cout;
using std::vector;
using std::string;

vector<vector<int>> g;
int dp[10][105][105];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int main() {
    freopen("./10_input.txt", "r", stdin); 
    std::string tmp_str;
    
    int flag = true;;
   	while(std::getline(std::cin, tmp_str)) {
		vector<int> cur_row;
        cur_row.push_back(0);
		for (auto val: tmp_str) {
			cur_row.push_back(val - '0');
		}
        cur_row.push_back(0);
        if (flag)g.push_back(vector<int>(cur_row.size(), 0));
        flag = false;
		g.push_back(cur_row);
   	}
    g.push_back(vector<int>(g[0].size(), 0));
    // for (auto val : g) {
    //     for (auto elem : val) {
    //         std::cout << elem << " ";
    //     }
    //     std::cout << '\n';
    // }

    int m = g.size() - 2;
    int n = g[0].size() - 2;

    // auto start = std::chrono::high_resolution_clock::now();
    for (int i = 1;i <= m;i++) {
        for (int j = 1;j <= n;j++) {
            dp[0][i][j] = (g[i][j] == 0) ? 1 : 0;
        }
    }

    for (int k = 1;k <= 9;k++) {
        for (int i = 1;i <= m;i++) {
            for (int j = 1;j <= n;j++) {
                for (int x = 0;x < 4;x++) {
                    int tx = i + dx[x];
                    int ty = j + dy[x];
                    if (g[i][j] - g[tx][ty] == 1) {
                        dp[k][i][j] += dp[k - 1][tx][ty];
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int i = 1;i <= m;i++) {
        for (int j = 1;j <= n;j++) {
            ans += dp[9][i][j];
        }
    }

    // auto end = std::chrono::high_resolution_clock::now();
    // auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    // std::cout << "Elapsed time: " << elapsed.count() << " ms\n";
    std::cout << ans << '\n';

    return 0;
}