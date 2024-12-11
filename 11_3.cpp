#include <iostream>
#include <unordered_map>
#include <cmath>
#include <string>
#include <sstream>

int getDigitCount(long long n) {
    if (n == 0) return 1;
    return static_cast<int>(std::log10(std::abs(n))) + 1;
}

int main() {
    std::unordered_map<long long, long long> stone_count;
    freopen("./11_3.txt", "r", stdin); 
    int flag = 0;
    
    std::string str;
    while(std::getline(std::cin, str)) {
        std::stringstream ss(str);
        
        long long tmp_num;
        while(ss >> tmp_num) {
            stone_count[tmp_num] = 1;
        }
    }

    int cnt = 0;
    while (cnt < 75) {
        std::unordered_map<long long, long long> new_stone;
        int dig_cnt = 0;
        for (const auto& [val, num] : stone_count) {
            if (val == 0) {
                new_stone[1] += num;
            } else if ((dig_cnt = getDigitCount(val)) % 2 == 0) {
                int half = dig_cnt / 2;
                long long fac = 1;
                while(half--) {fac *= 10;};
                new_stone[val / fac] += num;
                new_stone[val % fac] += num;
            } else {
                new_stone[val * 2024] += num;
            }
        }
        stone_count.swap(new_stone);
        cnt++;
        // std::cout << "[" << cnt << "]: " << new_stone.size() << '\n';
    } 

    long long result = 0;
    for (const auto& [val, num] : stone_count) {
        // std::cout << val << ": " << num << '\n';
        result += num;
    }
    std::cout << result << std::endl;

    return 0;
}