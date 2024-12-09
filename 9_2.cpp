#include <iostream>
#include <string>
#include <vector>
#include <map>

int main() {
    freopen("/Users/lyon/Desktop/TDDD38/adventOfCode2024/9_input.txt", "r", stdin);
    std::string str;
    std::vector<int> vec;
    std::map<std::pair<int, int>, int> mmap;
    int val = 0;
    while(std::getline(std::cin, str)) {
        for (int i = 0;i < str.size();i+=2) {
            int cnt = 0;
            while(cnt < (str[i] - '0')) {
                cnt++;
                vec.push_back(val);
            }   
            val++;
            cnt = 0;
            while(i + 1 < str.size() && cnt < (str[i + 1] - '0')) {
                cnt++;
                vec.push_back(-1);
            }
        }
    }
    
    int n = vec.size();
    int last_idx = n - 1;
    int first_idx = 0;
    while (vec[first_idx] != -1) {
            first_idx++;
    }

    while(last_idx >= 0) {
        // std::cout << "* " << last_idx << '\n';
        int st = last_idx;
        while(vec[last_idx] != -1 && vec[last_idx] == vec[st]) {
            last_idx--;
        }

        if (last_idx < 0) break;

        int len = 0;
        for (int i = 0;i < vec.size();i++) {
            if (i > last_idx) {
                break;
            }
            len = 0;
            if (vec[i] != -1)continue;
            while(vec[i] == -1) {
                len++;
                i++;
            }

            // std::cout << len << " " << st - last_idx << " " << vec[st] << std::endl; 
            if (len >= (st - last_idx)) {
                for (int j = 0;j < st - last_idx;j++) {
                    std::swap(vec[i - len + j], vec[st - j]);
                    // for (int i = 0;i < vec.size();i++) {
                    //     if (vec[i] == -1) {
                    //         putchar('.');
                    //     }
                    //     else std::cout << vec[i];
                    // }
                    // std::cout << '\n';
                }
                break;
            }
        }

        while(vec[last_idx] == -1) {
            last_idx--;
        }
    }

    long long ans = 0;
    for (long long i = 0;i < vec.size();i++) {
        if (vec[i] != -1) {
            ans += (long long)(vec[i]) * i;
        }
    }

    std::cout << ans << '\n';

    return 0;
}
