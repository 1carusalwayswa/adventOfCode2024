#include <iostream>
#include <string>
#include <vector>
#include <sstream>

long long ans = 0;
long long target;
std::vector<long long> vec;

long long combine(long long x, long long y) {
    if (y == 0) {
        return x * 10;
    }

    long long tmp = y;
    long long mul = 1;
    while (tmp > 0) {
        mul *= 10;
        tmp /= 10;
    }
    
    return x * mul + y;
}

bool dfs(int cur, long long res) {
    if (cur == vec.size()) {
        if (res == target) {
            return true;
        }
        return false;
    }

    return dfs(cur + 1, res + vec[cur]) || dfs(cur + 1, res * vec[cur])
    || dfs(cur + 1, combine(res, vec[cur]));
}

int main() {
    freopen("/Users/lyon/Desktop/TDDD38/adventOfCode2024/7_1_input.txt", "r", stdin);
    std::string tmp_str;
    while (std::getline(std::cin, tmp_str))
    {
        vec.clear();

        size_t pos = tmp_str.find(":");

        if (pos != std::string::npos) {
            target = std::stoll(tmp_str.substr(0, pos));

            // loop version
            // std::string numbers = tmp_str.substr(pos + 1);
            // std::stringstream ss(numbers);
            // long long value;

            // while(ss >> value) {
            //     vec.push_back(value);
            // }

            // no-loop version
            // std::istringstream iss(tmp_str.substr(pos + 1));
            // vec.insert(vec.end(), std::istream_iterator<int>(iss), std::istream_iterator<int>());
        }

        if (dfs(1, vec[0])) {
            ans += target;
        }
    }
    std::cout << ans << "\n";
    return 0;
}