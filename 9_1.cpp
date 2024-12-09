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
    for (int i = 0;i < vec.size();i++) {
        if (vec[i] == -1) {
            putchar('.');
        }
        else std::cout << vec[i];
    }
    std::cout << '\n';
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
    // while(first_idx < last_idx) {
    //     // std::swap(vec[first_idx], vec[last_idx]);
    //     int first_size = 0;
    //     int last_size = 0;
    //     std::cout << "----" << first_idx << " " << last_idx << '\n';
    //     int l = first_idx;
    //     while(vec[l] == -1) {
    //         l++;
    //         // std::cout << 1 << '\n';
    //     }
    //     first_size = l - first_idx;

    //     int r = last_idx;
    //     while(vec[r] == vec[last_idx]) {
    //         r--; 
    //     };
    //     last_size = last_idx - r;

    //     if (last_size > first_size) {
    //         last_idx = r;
    //         while(last_idx > first_idx && vec[last_idx] == -1){
    //             last_idx--;
    //         };
            
    //         continue;

    //         if (first_idx >= last_idx) {
    //             int l = 0;
    //             while(vec[l] != -1 && l < n) {
    //                 l++;
    //             }

    //             first_idx = l;
    //             // last_idx = r;

    //             // if (mmap.find({first_idx, last_idx}) != mmap.end() && mmap[{first_idx, last_idx}] > 5) {
    //             //     std::cout << first_idx << " " << last_idx << '\n';
    //             //     std::cout << mmap[{first_idx, last_idx}] << '\n'; 
    //             //     break;
    //             // }
    //             // if (mmap.find({first_idx, last_idx}) == mmap.end())mmap[{first_idx, last_idx}] = 1;
    //             // else mmap[{first_idx, last_idx}] += 1;
    //         }
    //     }

    //     while (first_idx < l && last_idx > r && first_idx < last_idx) {
    //         // std::cout << "*" << first_idx << " " << last_idx << '\n';
    //         std::swap(vec[first_idx], vec[last_idx]);
    //         first_idx++;
    //         last_idx--;
    //         for (int i = 0;i < vec.size();i++) {
    //             if (vec[i] == -1) {
    //                 putchar('.');
    //             }
    //             else std::cout << vec[i];
    //         }
    //         std::cout << '\n';
    //         // std::cout << "@" << first_idx << " " << last_idx << '\n';
    //     }


    //     // first_idx = l;
    //     last_idx = r;
    //     while(first_idx < last_idx && vec[first_idx] != -1){
    //         first_idx++;
    //     };
    //     while(last_idx > first_idx && vec[last_idx] == -1){
    //         last_idx--;
    //     };

    //     if (first_idx >= last_idx) {
    //         int l = 0;
    //         while(vec[l] != -1 && l < n) {
    //             l++;
    //         }

    //         first_idx = l;
    //         // if (mmap.find({first_idx, last_idx}) != mmap.end() && mmap[{first_idx, last_idx}] > 5) {
    //         //     // std::cout << first_idx << " " << last_idx << '\n';
    //         //     // std::cout << mmap[{first_idx, last_idx}] << '\n'; 
    //         //     break;
    //         // }
    //         // if (mmap.find({first_idx, last_idx}) == mmap.end())mmap[{first_idx, last_idx}] = 1;
    //         // else mmap[{first_idx, last_idx}] += 1;
    //     }
    // }

    // for (int i = 0;i < 500;i++) {
    //     if (vec[i] == -1) {
    //         putchar('_');
    //     }
    //     else std::cout << vec[i];

    //     std::cout << ' ';
    // }
    // std::cout << '\n';
    // for (int i = vec.size() - 1;i >= vec.size() - 500;i--) {
    //     if (vec[i] == -1) {
    //         putchar('.');
    //     }
    //     else std::cout << vec[i];

    //     std::cout << ' ';
    // }
    // std::cout << '\n';
    

    long long ans = 0;
    for (long long i = 0;i < vec.size();i++) {
        if (vec[i] != -1) {
            ans += (long long)(vec[i]) * i;
            // if (i < 500)std::cout << vec[i] << "*" << i << "=" << (vec[i]) * i<<'\n'; 
        }
        // if (!((vec[i] == '.')) {
        //     std::cout << i << " No" << '\n';
        //     std::cout << vec[i] << '\n';
        //     break;
        // }
        // std::cout << vec[i];
    }
    // std::cout << '\n';

    std::cout << ans << '\n';

    return 0;
}
