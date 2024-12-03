#include <iostream>
#include <string>
#include <stack>

std::string str;

bool check_valid(int l, int r, int& res) {
    bool a_flag = false;
    int cnt = 0;
    int a = 0;
    int i;

    for (i = l; i < r; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            cnt++;
            continue;
        } else if (str[i] == ',') {
            a = std::stoi(str.substr(i - cnt, cnt));
            int ta = a;

            int num_len = 0;
            while(ta) {
                ta /= 10;
                num_len++;
            }

            if (num_len >= 1 && num_len <= 3) {
                break;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    i++;
    int ori_i = i;
    if (i == r) return false;
    for (; i < r; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }
    int b = std::stoi(str.substr(ori_i, r - ori_i));
    int tb = b;

    int num_len = 0;
    while(tb) {
        tb /= 10;
        num_len++;
    }
    if (num_len < 1 && num_len > 3) {
        return false;;
    }

    // std::cout << "a: " << a << " " << "b: " << b << std::endl;
    res = a*b;
    return true;
}

int main() {
    long long ans = 0;
    int cnt_seg = 0;
    bool dont = false;
    while(getline(std::cin, str)) {
        if (str.length() == 0) continue;
        cnt_seg++;
        int a, b;
        a = b = 0;
        for (int i = 0;i < str.size() - 4;i++) {
            if (str.substr(i, 7) == "don't()") {
                dont = true;
                i = i + 6;
                continue;
            }

           if (str.substr(i, 4) == "do()") {
                dont = false;
                i = i + 3;
                continue;
            } 

            if(dont) {
                continue;
            }

            if (str.substr(i, 4) == "mul(") {
                int dot_cnt = 0;
                for (int j = i + 4; j < str.size(); j++) {
                    if (str.substr(j, 7) == "don't()") {
                            dont = true;
                            i = j + 6;
                            break;
                    }

                    if (str.substr(j, 4) == "do()") {
                            dont = false;
                            i = j + 3;
                            break;
                    } 

                    if (str[j] == ')') {
                        int tmp_cnt = 0;
                        // std::cout << "case " << tmp_cnt++ << ":" << str.substr(i, j - i + 1) << '\n';
                        int res = 0;
                        check_valid(i + 4, j, res);
                        ans += res;
                        i = j;
                        break;
                    } else if (str[j] >= '0' && str[j] <= '9') {
                        continue;
                    } else if (str[j] == ',' && dot_cnt == 0) {
                        dot_cnt++;
                        continue;
                    } else {
                        i = j - 1;
                        break;
                    }
                }
            }
        }
    }

    std::cout << ans << " " << cnt_seg << '\n'; 
    return 0;
}