'''
I try to solve part2 by the same idea I learned from day 17 part 2.
Generating string basic on some specific rule.
In this problem, demand to shortest path, so there always has two step of one move,
one in x, other one in y
But the weird thing is the different order of these two steps(first x or first y)will make different
length of the string which be generated in the next next round.
It really take me a lot time to figure out the pattern it is, but I am falied,
I learn a new idea from other people (sry, I dont remeber who exactly is)
Basically, it try all possible order and get the shortest one.
So I refactor my code in a recursive way, and it work well.
I think solve questions by generator is the secondest thing I learned from aoc 2024.
'''
from aocd.models import Puzzle
from functools import cache

puzzle = Puzzle(2024, 21)
input = puzzle.input_data.strip().split('\n')
# input = ["029A", "980A", "179A", "456A", "379A"]

num_keyboard = [
    ['7', '8', '9'],
    ['4', '5', '6'],
    ['1', '2', '3'],
    ['#', '0', 'A']
]

dir_keyboard = [
    ['#', '^', 'A'],
    ['<', 'v', '>']
]

num_keyboard_set = {num_keyboard[i][j]: (i, j) for i in range(len(num_keyboard)) for j in range(len(num_keyboard[i]))}
dir_keyboard_set = {dir_keyboard[i][j]: (i, j) for i in range(len(dir_keyboard)) for j in range(len(dir_keyboard[i]))}

@cache
def generate_str(from_, to_, cur, end):
    if cur > end:
        return 1
    
    keyboard, key_set = (num_keyboard, num_keyboard_set) if cur == 0 else (dir_keyboard, dir_keyboard_set)
    x, y = key_set[from_]
    dx = key_set[to_][0] - key_set[from_][0]
    dy = key_set[to_][1] - key_set[from_][1]
    # print(to_, key_set[to_][0], key_set[to_][1])

    ch_y = '>' if dy > 0 else '<'
    ch_x = 'v' if dx > 0 else '^'

    dxs = ch_x * abs(dx) if dx != 0 else ""
    dys = ch_y * abs(dy) if dy != 0 else ""

    possible_path = []

    if keyboard[x + dx][y] != '#':
        path = "A" + dxs + dys + "A"
        c = sum(generate_str(a, b, cur + 1, end) for a, b in zip(path, path[1:]))
        possible_path.append(c)

    if keyboard[x][y + dy] != '#':
        path = "A" + dys + dxs + "A"
        c = sum(generate_str(a, b, cur + 1, end) for a, b in zip(path, path[1:]))
        possible_path.append(c)
    
    return min(possible_path)

def solve(n):
    ans = 0
    for line in input:
        c = sum(generate_str(a, b, 0, n) for a, b in zip("A" + line, line))
        ans += c * int(line[:-1])
        # print(c)
    return ans
    

if __name__ == "__main__":
    puzzle.answer_a = solve(2) 
    # print(puzzle.answered_a)
    puzzle.answer_b = solve(25)
    # print(puzzle.answered_b)
'''
+---+---+---+
| 7 | 8 | 9 |
+---+---+---+
| 4 | 5 | 6 |
+---+---+---+
| 1 | 2 | 3 |
+---+---+---+
    | 0 | A |
    +---+---+

   +---+---+
    | ^ | A |
+---+---+---+
| < | v | > |
+---+---+---+
'''

