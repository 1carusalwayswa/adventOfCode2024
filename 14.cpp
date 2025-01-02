#include "./utils.hpp"
#include <unordered_map>

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

struct node{
    int x,y;
    int x_step, y_step;
};

vector<node> vec;
unordered_map<pair<int,int>, int, pair_hash> point_count;
int m = 103;
int n = 101;

int judge(int x, int y) {
    int mid_x = (m + 1) / 2;
    int mid_y = (n + 1) / 2;
    
    if (x < mid_x) {
        if (y < mid_y) return 0;
        else if (y > mid_y)return 1;
        return 4;
    } 

    if (x > mid_x) {
        if (y < mid_y) return 2;
        else if (y > mid_y)return 3;
        return 4;
    }

    return 4;
}

int main() {
    freopen("/Users/lyon/Desktop/TDDD38/adventOfCode2024/14_input.txt", "r", stdin); 
    freopen("/Users/lyon/Desktop/TDDD38/adventOfCode2024/14_output.txt", "w", stdout); // 重定向输出到文件
    
    string line;
    node tmp;
    while(scanf("p=%d,%d v=%d,%d", &tmp.x, &tmp.y, &tmp.y_step, &tmp.x_step) == 4) {
        // cout << tmp.x << " " << tmp.y << " " << tmp.x_step << " " << tmp.y_step << '\n';
        tmp.x += 1;
        tmp.y += 1;
        swap(tmp.x, tmp.y);
        vec.push_back(tmp);
        getchar();
    }

    int T = 20000;
    while(T--) {
        vector<vector<int>> grid(m + 1, vector(n + 1, 0));
        bool flag = true;
        for (auto& val : vec) {
            // cout << "before: " << val.x << " " << val.y << " " << T << '\n';
            val.x = (val.x + val.x_step + m - 1) % m + 1;
            val.y = (val.y + val.y_step + n - 1) % n + 1;
            grid[val.x][val.y] += 1;
            if (grid[val.x][val.y] > 1)flag = false;
            // cout << "after: " << val.x << " " << val.y << " " << T << '\n';
        }
        if (!flag)continue;
        cout << 20000 - T << '\n';
        for (size_t i = 0;i < m;i++) {
            for (size_t j = 0;j < n;j++) {
                cout << grid[i][j];
            }
            cout << '\n';
        }
        cout << '\n';
    }

    for (const auto& val : vec) {
        point_count[{val.x, val.y}]++;
    }

    vector<int> ans(5, 0);
    for (const auto& [pos, cnt] : point_count) {
        // cout << pos.first << " " << pos.second << " " << cnt << '\n';
        ans[judge(pos.first, pos.second)] += cnt;
    }
    
    long long res = 1;
    for (auto val: ans) {
        cout << val << '\n';
        res *= val;
    }
    res /= ans[4];
    cout << res << '\n';
}