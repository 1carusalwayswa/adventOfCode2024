#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

std::vector<std::vector<int>> g;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0}; 
int vis[1005][1005];
bool target[50][50][50][50];

struct node {
	int x,y;
	int cost;
	int ori_x, ori_y;
};

void bfs() {
	std::queue<node> que;
	for (int i = 0;i < g.size();i++) {
		for (int j = 0;j < g[i].size();j++) {
			if (g[i][j] == 9) {
				que.push((node){i, j, 0,i, j});
			}
		}
	}
	int m = g.size();
	int n = g[0].size();

	while (!que.empty()) {
		node cur = que.front();
		que.pop();

		if (g[cur.x][cur.y] == 0 && cur.cost == 9) {
			// if (target[cur.x][cur.y][cur.ori_x][cur.ori_y] == 0) { // use this for part 1
				vis[cur.x][cur.y] += 1;
				// target[cur.x][cur.y][cur.ori_x][cur.ori_y] = 1;	
			// }
			continue;
		}

		for (int i = 0;i < 4;i++) {
			int tx = cur.x + dx[i];
			int ty = cur.y + dy[i];
			
			if (tx >= 0 && tx < m && ty >= 0 && ty <= n && (g[cur.x][cur.y] - g[tx][ty] == 1)) {
				que.push((node){tx, ty, cur.cost + 1, cur.ori_x, cur.ori_y});
			}
		}
	}
}

int main() {
	freopen("./10_input.txt", "r", stdin); 
   	std::string tmp_str;
   	while(std::getline(std::cin, tmp_str)) {
		std::vector<int> cur_row;
		for (auto val: tmp_str) {
			cur_row.push_back(val - '0');
		}
		g.push_back(cur_row);
   	}

	bfs();

	int ans = 0;
	for (int i = 0;i < g.size();i++) {
		for (int j = 0;j < g[0].size();j++) {
			if (g[i][j] == 0) {
				ans += vis[i][j];
			}
			std::cout << vis[i][j] << " ";
		}
		std::cout << '\n';
	}

	std::cout << ans << '\n';

	return 0;
}