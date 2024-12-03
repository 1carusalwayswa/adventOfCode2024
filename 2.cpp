#include <iostream>
#include <sstream>
#include <vector>
#include <string>

int main() {
    std::string line;
    int ans = 0;
    int cnt = 0;
    while(std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::vector<int> numbers;
        std::vector<int> numbers_ori;
        int num;

        while(ss >> num) {
            numbers_ori.push_back(num);
        }

        int len = numbers_ori.size();
        for (int k = -1; k < len; k++) {
            // std::cout << 1 << std::endl;
            numbers.clear();
            for (int i = 0; i < numbers_ori.size(); i++) {
                if (i == k) continue;
                numbers.push_back(numbers_ori[i]);
            }

            // for(int i = 0;i < numbers.size();i++) {
            //     std::cout << numbers[i] << " ";
            // }
            // putchar('\n');

            int res = true;
            int dir = numbers[1] - numbers[0];
            for (int i = 2; i < numbers.size(); i++) {
                if ((numbers[i] - numbers[i - 1]) * dir <= 0) {
                    res = false;
                    break;
                }
                int diff = abs(numbers[i] - numbers[i - 1]);
                if (diff < 1 || diff > 3) {
                    res = false;
                    break;
                }
            } 
            cnt++;
            dir = abs(dir);
            if (res && (dir >= 1 && dir <= 3)) {
                ans++;
                break;
            }
        }
    }
    std::cout << "* " << ans << std::endl;
    return 0;
}