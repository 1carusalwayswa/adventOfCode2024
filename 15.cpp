#include "./utils.hpp"
#include <stack>

struct node {
	int x,y;
};

node st;
vector<string> g;
vector<string> op;

bool is_valid(int x, int y) {
	return x >= 0 && x < g.size() && y >= 0 && y < g[0].size();
}

node get_step(char ch, bool p2) {
	int k = p2 ? 2 : 1;
	if (ch == '^') return {-1 * k, 0};
	if (ch == 'v') return {1 * k, 0};
	if (ch == '<') return {0, -1 * k};
	if (ch == '>') return {0, 1 * k};
	return {-99999, -99999};
}

void move_box(node st, node ed, node step) {
	while(st.x != ed.x || st.y != ed.y) {
		if (g[st.x][st.y] == '[')g[st.x][st.y] = ']';
		else if (g[st.x][st.y] == ']')g[st.x][st.y] = '[';
		st.x += step.x;
		st.y += step.y;

	}
}

void handle(char ch) {
	node step = get_step(ch, false);
	
	node ed = st;
	ed.x += step.x;
	ed.y += step.y;	
	while (is_valid(ed.x, ed.y) && g[ed.x][ed.y] == 'O') {
		ed.x += step.x;
		ed.y += step.y;
	}
	
	if (g[ed.x][ed.y] == '.') {
		node one_step = st;
		one_step.x += step.x;
		one_step.y += step.y;

		swap(g[ed.x][ed.y], g[one_step.x][one_step.y]);
		swap(g[st.x][st.y], g[one_step.x][one_step.y]);
		st = one_step;
	}
}

bool is_power(int x, int y) {
    if (g[x][y] == '[') return true;
    if (g[x][y] == ']') return true;
    if (g[x][y] == '@') return true;
    return false;
}

void swap_rows(int row1, int row2, int start_col, int end_col) {
    if (row1 >= g.size() || row2 >= g.size() || 
        start_col >= g[row1].size() || end_col > g[row1].size() ||
        start_col >= g[row2].size() || end_col > g[row2].size()) {
        return;
    }
    
    std::swap_ranges(
        g[row1].begin() + start_col,
        g[row1].begin() + end_col,
        g[row2].begin() + start_col
    );
}

vector<node> get_border_y_new(node cur, vector<node> last_borders, node step) {
    vector<node> ans;
	node next = cur;
    next.x -= step.x;
    next.y -= step.y;

    for (auto last_border : last_borders) {
        int l_extra = last_border.x - 1;
        if (g[cur.x][l_extra] != '[') l_extra += 1;
        int r_extra = last_border.y + 1;
        if (g[cur.x][r_extra] != ']') r_extra -= 1;
        int last_l, last_r;
        int flag_st = false;
        
        for (int i = l_extra;i <= r_extra;i++) {
            if (g[cur.x][i] == '[') {
                if (is_power(next.x, i) || is_power(next.x, i + 1)) {
                    if (!flag_st) {
                        last_l = i;
                        flag_st = true;
                    } 
                } else if (flag_st){
                    last_r = i - 1;
                    ans.push_back((node){last_l, last_r});
                    flag_st = false;
                    i = i + 1;
                }
            }
            if (flag_st && (g[cur.x][i] == '.' || g[cur.x][i] == '#')) {
                ans.push_back((node){last_l, i - 1});
                flag_st = false;
            }
        }
        if (flag_st)ans.push_back((node){last_l, r_extra}); 

        if (last_border.x > last_border.y) {
            // cout << "here" << '\n';
        }

        // cout << "before:  " << l_extra << " " << r_extra << '\n';
        // cout << "after:  " << last_border.x << " " << last_border.y << '\n';
    }
	return ans;
}

void handle_part2(char ch) {
	node step = get_step(ch, false);
	
	node ed = st;
	node one_step = st;
	one_step.x += step.x;
	one_step.y += step.y;

	if (step.y) {
		ed.x += step.x;
		ed.y += step.y;
		while (is_valid(ed.x, ed.y) && g[ed.x][ed.y] != '.' && g[ed.x][ed.y] != '#') {
			ed.x += step.x;
			ed.y += step.y;
		}
		if (g[ed.x][ed.y] == '#')return;
		move_box(one_step, ed, step);
		swap(g[ed.x][ed.y], g[one_step.x][one_step.y]);	
		swap(g[st.x][st.y], g[one_step.x][one_step.y]);
	} else {
		ed.x += step.x;
		ed.y += step.y;	
        vector<node> last_borders;
        last_borders.push_back((node){st.y, st.y});
		while (is_valid(ed.x, ed.y)) {
            node next = ed;
			last_borders = get_border_y_new(ed, last_borders, step);
			bool flag = true;
			for (auto& last_border : last_borders) {
                // cout << last_border.x << " " << last_border.y << '|';
            }
            // std::cout << '\n';
            if (last_borders.size() == 0)break;

			ed.x += step.x;
			ed.y += step.y;
		}
        // std::cout << ed.x << '\n';
		if (g[one_step.x][one_step.y] == '#')return;

		node cur = st;
		cur.x += step.x;
		cur.y += step.y;
		node last = st;
        last_borders.clear();
        last_borders.push_back((node){st.y, st.y});
		stack<vector<node>> sta_;
		sta_.push((vector<node>){(node){st.y, st.y}});
		while (cur.x != ed.x) {
            vector<node> cur_borders;
			cur_borders = get_border_y_new(cur, last_borders, step);
            last_borders = cur_borders;
			sta_.push(cur_borders);
			node next = cur;
			next.x += step.x;
			next.y += step.y;
			for (const auto& last_border : cur_borders) {
                // cout << last_border.x << " " << last_border.y << '|';
				for (int i = last_border.x; i <= last_border.y; i++) {
					if (g[next.x][i] == '#' && (g[cur.x][i] == '[' || g[cur.x][i] == ']')) {
						return;
					}
				}
			}
            // cout << '\n';
			cur.x += step.x;
			cur.y += step.y;
		}

		cur = ed;
		cur.x -= step.x;
		cur.y -= step.y;
		last = ed;	
		while (cur.x != st.x) {
			vector<node> borders = sta_.top();
			sta_.pop();
            for (auto border: borders) {
			    swap_rows(cur.x, last.x, border.x, border.y + 1);
            }
			last = cur;
			cur.x -= step.x;
			cur.y -= step.y;
		}
		swap(g[st.x][st.y], g[one_step.x][one_step.y]);
	}
	st = one_step;
}

int main() {
	freopen("/Users/lyon/Desktop/TDDD38/adventOfCode2024/15_input.txt", "r", stdin);
	freopen("/Users/lyon/Desktop/TDDD38/adventOfCode2024/15_output.txt", "w", stdout);
	g = readMat<char>();
	auto loc = find_if(std::begin(g), std::end(g), [](string str) {
		return str.size() == 0;
	});
    op.assign(loc + 1, g.end());
    g.erase(loc, g.end());
	// cout << g.size() << " " << op.size() << '\n';

	for (auto& line : g) {
		string newLine;
		for (char c : line) {
			if (c == '.') newLine += "..";
			else if (c == '#') newLine += "##";
			else if (c == 'O') newLine += "[]";
			else if (c == '@') newLine += "@.";
			else newLine += c;  // 保持其他字符不变
		}
		line = newLine;
	}

	for (size_t i = 0;i < g.size();i++) {
		for (size_t j = 0;j < g[0].size();j++) {
			if (g[i][j] == '@') {
				st.x = i;
				st.y = j;
			}
		}
	}

	for (auto g_line : g) {
		cout << g_line << '\n';
	}
	cout << '\n';

	int cnt = 0;
	for (auto line : op) {
		for (auto ch: line) {
			handle_part2(ch);
            // if (cnt > 1001)continue;
			// cout << "Move " << ch << ":" << '\n';
			// for (auto g_line : g) {
			// 	cout << g_line << '\n';
			// }
			// cout << '\n';
            // cnt++;
		}
	}

	// for (auto g_line : g) {
	// 	cout << g_line << '\n';
	// }
	// cout << '\n';

	long long ans = 0;
	for (size_t i = 0;i < g.size();i++) {
		for (size_t j = 0;j < g[0].size();j++) {
			if (g[i][j] == '[') {
				ans += i * 100 + j; 
				// cout << ans << '\n';
				// std::cout << i << " " << j << '\n';
			}
		}
	}

	cout << ans << '\n';
}