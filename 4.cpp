#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> g;
int target[1005][1005];
int m, n;
char path[4] = {'M', 'M', 'S', 'S'};

int check_valid(int x, int y) {
    int ans = 0;
    // right
    std::string tmp_str {};
    for (int i = y; i < n && abs(i - y) < 4; i++) {
        tmp_str += g[x][i];
    }
    if (tmp_str == "XMAS") {
        ans++;

        for (int i = y; i < n && abs(i - y) < 4; i++) {
            // tmp_str += g[x][i];
            target[x][i] = 1;
        } 
    }

    // down
    tmp_str = "";
    for (int i = x; i < m && abs(i - x) < 4; i++) {
        tmp_str += g[i][y];
    }
    if (tmp_str == "XMAS") {
        ans++;
        for (int i = x; i < m && abs(i - x) < 4; i++) {
            // tmp_str += g[i][y];
            target[i][y] = 1;
        }
    }

    // left
    tmp_str = "";
    for (int i = y; i >= 0 && abs(i - y) < 4; i--) {
        tmp_str += g[x][i];
    }
    if (tmp_str == "XMAS") {
        ans++;

        for (int i = y; i >= 0 && abs(i - y) < 4; i--) {
            // tmp_str += g[x][i];
            target[x][i] = 1;
        }
    }

    // top
    tmp_str = "";
    for (int i = x; i >= 0 && abs(i - x) < 4; i--) {
        tmp_str += g[i][y];
    }
    if (tmp_str == "XMAS") {
        ans++; 
        for (int i = x; i >= 0 && abs(i - x) < 4; i--) {
            // tmp_str += g[i][y];
            target[i][y] = 1;
        }
    } 

    // Diagonal-down
    int tx = x;
    int ty = y;
    tmp_str = "";
    while(tx < m && ty < n && abs(x - tx) < 4 && abs(y - ty) < 4) {
        tmp_str += g[tx][ty];
        tx++;
        ty++;
    }
    if (tmp_str == "XMAS") {
        ans++;

        tx = x;
        ty = y;
        while(tx < m && ty < n && abs(x - tx) < 4 && abs(y - ty) < 4) {
            // tmp_str += g[tx][ty];
            target[tx][ty] = 1;
            tx++;
            ty++;
        }
    } 

    // Diagonal-up
    tx = x;
    ty = y;
    tmp_str = "";
    while(tx >= 0 && ty >= 0 && abs(x - tx) < 4 && abs(y - ty) < 4) {
        tmp_str += g[tx][ty];
        tx--;
        ty--;
    }
    if (tmp_str == "XMAS") {
        ans++;

        tx = x;
        ty = y;
        while(tx >= 0 && ty >= 0 && abs(x - tx) < 4 && abs(y - ty) < 4) {
            // tmp_str += g[tx][ty];
            target[tx][ty] = 1;
            tx--;
            ty--;
        }
    }

    // Anti-Diagonal-down
    tx = x;
    ty = y;
    tmp_str = "";
    while(tx < m && ty >= 0 && abs(x - tx) < 4 && abs(y - ty) < 4) {
        tmp_str += g[tx][ty];
        tx++;
        ty--;
    }
    if (tmp_str == "XMAS") {
        ans++;
        tx = x;
        ty = y;
        while(tx < m && ty >= 0 && abs(x - tx) < 4 && abs(y - ty) < 4) {
            // tmp_str += g[tx][ty];
            target[tx][ty] = 1;
            tx++;
            ty--;
        }
    } 

    // Anti-Diagonal-up
    tx = x;
    ty = y;
    tmp_str = "";
    while(tx >= 0 && ty < n && abs(x - tx) < 4 && abs(y - ty) < 4) {
        tmp_str += g[tx][ty];
        tx--;
        ty++;
    }
    if (tmp_str == "XMAS") {
        ans++;

        tx = x;
        ty = y;
        while(tx >= 0 && ty < n && abs(x - tx) < 4 && abs(y - ty) < 4) {
            // tmp_str += g[tx][ty];
            target[tx][ty] = 1;
            tx--;
            ty++;
        }
    } 

    return ans;
}

int valid_location(int x, int y) {
    return x >= 0 && x < m && y >= 0 && y < n;
}
int check_valid_x(int x, int y, int st) {
    // left-top
    if (!valid_location(x - 1, y - 1) || g[x-1][y-1] != path[st]) {
        return 0;
    }

    // right-top
    if (!valid_location(x - 1, y + 1) || g[x-1][y+1] != path[(st + 1) % 4]) {
        return 0;
    }

    // right-down
    if (!valid_location(x + 1, y + 1) || g[x+1][y+1] != path[(st + 2) % 4]) {
        return 0;
    }

    // left-down
    if (!valid_location(x + 1, y - 1) || g[x+1][y-1] != path[(st + 3) % 4]) {
        return 0;
    }

    target[x-1][y-1] = 1;
    target[x-1][y+1] = 1;
    target[x+1][y-1] = 1;
    target[x+1][y+1] = 1;

    target[x][y] = 1;
    return 1;
}

int main() {
    freopen("/Users/lyon/Desktop/TDDD38/adventOfCode2024/4_input.txt", "r", stdin);

    std::string tmp_str;
    while(getline(std::cin, tmp_str)) {
        // if (tmp_str == "*")break;
        g.push_back(tmp_str);
    }

    m = g.size();
    n = g[0].size();
    // std::cout << g[0].size() << '\n';

    int ans = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (g[i][j] == 'A') {
                for (int k = 0; k < 4; k++) {
                    if (check_valid_x(i, j, k)) {
                        ans++;
                    }
                }
            }
        }
    }

    std::cout << ans << '\n';
    // for (int i = 0; i < m; i++) {
    //     for (int j = 0; j < n; j++) {
    //         if (target[i][j]) {
    //             std::cout << g[i][j];
    //         }
    //         else std::cout << '.';
    //     }
    //     putchar('\n');
    // }
    return 0;
}