from aocd.models import Puzzle
from functools import cache
import sys
from collections import defaultdict
sys.setrecursionlimit(30000)

puzzle = Puzzle(2024, 22)
input = puzzle.input_data.split('\n')
price = []

@cache
def dfs(val, cnt):
    if cnt == 2000:
        price.append(val % 10)
        return val
    
    res = val * 64
    val = (val ^ res) % 16777216
    res = val // 32
    val = (val ^ res) % 16777216 
    res = val * 2048
    val = (val ^ res) % 16777216 
    price.append(val % 10)
    
    return dfs(val, cnt + 1)

if __name__ == "__main__":
    ans = 0
    prices = []
    diffs = []
    for line in input:
        price = []
        ans += dfs(int(line), 0)
        diff = [price[i] - price[i - 1] for i in range(1, len(price))]
        diffs.append(diff)
        prices.append(price)
    puzzle.answer_a = ans

    substr_cnt = defaultdict(int)
    diff_substrs = []
    len_sum = 0
    for i, diff in enumerate(diffs):
        current_substrs = defaultdict(int)
        for j in range(len(diff) - 3):
            substr = tuple(diff[j:j+4])
            if substr not in current_substrs:
                extra_value = prices[i][j+4]
                current_substrs[substr] = extra_value
        len_sum += len(current_substrs)
        diff_substrs.append(current_substrs)

    print(len_sum)

    for current_substrs in diff_substrs:
        for substr in current_substrs:
            if substr not in substr_cnt:
                count = sum(other_substrs[substr] for other_substrs in diff_substrs
                        if substr in other_substrs.keys())
                substr_cnt[substr] = count

    max_str, maxx = max(substr_cnt.items(), key=lambda x: x[1], default=("", 0))
    print(maxx, max_str)
    puzzle.answer_b = maxx
