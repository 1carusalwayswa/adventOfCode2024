#include <queue>
#include "./utils.hpp"
#include <regex>

struct node {
    long long x, y;
};

bool solve(long long x1, long long x2, long long x3, long long y1, long long y2, long long y3, long long& k1, long long& k2) {
        long long a = x1 * y2 - x2 * y1;
        long long c = x3 * y2 - x2 * y3;
        
        if (a == 0) {
            return false;
        }
        
        k1 = c / a;
        if (c % a != 0) {
            return false;
        }
        
        k2 = (x3 - x1 * k1) / x2;
        if ((x3 - x1 * k1) % x2 != 0) {
            return false;
        }
        
        if (y1 * k1 + y2 * k2 != y3) {
            return false;
        }
        
        return true;
}

node but[3];
long long min_cost;

int main() {
    freopen("/Users/lyon/Desktop/TDDD38/adventOfCode2024/13_input.txt", "r", stdin); 
    string str;
    int cnt = 0;
    std::string line;
    std::regex re("[-]?\\d+");
    
    long long ans = 0;
    while(std::getline(std::cin, line)) {
        cnt = 0;
        min_cost = 0x3f3f3f3f;
        while (cnt < 3 && std::getline(std::cin, line)) {
            std::sregex_iterator next(line.begin(), line.end(), re);
            std::sregex_iterator end;
            long long values[2];
            int i = 0;
            while (next != end) {
                std::smatch match = *next;
                // cout << match.str() << '\n';
                values[i++] = std::stoll(match.str());
                next++;
            }
            // cout << values[0] << " " << values[1] << " " << cnt << '\n';
            but[cnt].x = values[0];
            but[cnt].y = values[1]; 
            cnt++;
        }
        if (cnt < 3)break;
        but[2].x += 10000000000000;
        but[2].y += 10000000000000;
        // cout << but[0].x << " " << but[0].y << '\n';
        // cout << but[1].x << " " << but[1].y << '\n';

        long long k1, k2;
        if (solve(but[0].x, but[1].x, but[2].x, but[0].y, but[1].y, but[2].y, k1, k2)) {
            long long cur_cost = k1 * 3 + k2;
            ans += cur_cost;
        }
        
    }
    cout << "---" << ans << '\n';
    
    return 0;
}