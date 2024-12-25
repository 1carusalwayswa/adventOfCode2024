# cache is awesome
# handle string with python always save a lot of mental workload
from aocd.models import Puzzle
from functools import cache

puzzle = Puzzle(2024, 19)
# input = puzzle.examples[0].input_data.split('\n')
input = puzzle.input_data.split('\n')
towels = [t.strip() for t in input[0].split(',')]

@cache
def dfs(cur_design) -> int:
    if cur_design == "":
        return 1
    ans = 0
    for towel in towels:
        if len(towel) > len(cur_design):
            continue
        if cur_design[:len(towel)] == towel:
            ans += dfs(cur_design[len(towel):])
    return ans


if __name__ == "__main__":
    print(input)
    input = input[2:]

    p1 = 0
    p2 = 0
    for line in input:
        print("now: " + line)
        cnt = dfs(line)
        if cnt != 0:
            p1 += 1
        p2 += cnt 
    puzzle.answer_a = p1
    puzzle.answer_b = p2
    
