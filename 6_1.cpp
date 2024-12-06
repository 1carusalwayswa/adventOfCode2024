#include <iostream>
#include <string>
#include <queue>

struct node {
    int x, y;
    int dir;
    int cost;
};

std::string g[1005];
int m, n;
int ans;
int vis[1005][1005];
int dir_step_x[4] = {-1, 0, 1, 0};
int dir_step_y[4] = {0, 1, 0, -1};

bool is_valid(int x, int y) {
    if (x < 0 || y < 0) return false;

    if (x >= m || y >= n) return false;

    return true;
} 

void bfs() {
    node st;
    for (int i = 0;i < m;i++) {
        for (int j = 0; j < g[i].size(); j++) {
            if (g[i][j] == '^') {
                st.x = i;
                st.y = j;
                st.cost = 0;
                st.dir = 0;
                break;
            }
        }
    }

    std::queue<node> que;
    vis[st.x][st.y] = 1;
    que.push(st);

    while(!que.empty()) {
        node st = que.front();
        // std::cout << "cur: " << st.x << " " << st.y << '\n';
        que.pop();

        int step_x = dir_step_x[st.dir];
        int step_y = dir_step_y[st.dir];
        // std::cout << step_x << " " << step_y << '\n';

        int tx = st.x + step_x;
        int ty = st.y + step_y;
        int now_cost = 0;
        while(is_valid(tx, ty) && g[tx][ty] != '#') {
            vis[tx][ty] = 1;
            tx += step_x;
            ty += step_y;
            now_cost++;
            // std::cout << "loop: " << tx << " " << ty << '\n';
        }

        if (!is_valid(tx, ty)) {
            break;
        }
        que.push({tx - step_x, ty - step_y, (st.dir + 1) % 4, now_cost});
    }

    int ans = 0;
    for (int i = 0;i < m;i++) {
        for (int j = 0; j < g[i].size(); j++) {
            if (vis[i][j] == 1) {
                ans++;
                // std::cout << 'X';
            } else {
                // std::cout << g[i][j];
            }
            
        }
        std::cout << '\n';
    }
    printf("%d\n", ans);
}

int main() {
    freopen("/Users/lyon/Desktop/TDDD38/adventOfCode2024/6_input.txt", "r", stdin);

    int str_cnt = 0;
    while(std::getline(std::cin, g[str_cnt++]));

    m = str_cnt;
    n = g[0].size();

    bfs();

    return 0;
}