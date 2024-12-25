from aocd.models import Puzzle

puzzle = Puzzle(2024, 25)
input = puzzle.input_data.split("\n\n")

key_set = set()
for grid in input:
    # print(grid)
    grid = grid.split('\n')
    if grid[0] == "#####":
        continue
    heigh = [-1] * 5
    for i in range(len(grid)):
        for j in range(len(grid[i])):
            if grid[i][j] == '#':
                heigh[j] += 1
    # print(heigh)
    key_set.add(tuple(heigh))

lock_set = set()
for grid in input:
    # print(grid)
    grid = grid.split('\n')
    if grid[0] != "#####":
        continue
    heigh = [-1] * 5
    for i in range(len(grid)):
        for j in range(len(grid[i])):
            if grid[i][j] == '#':
                heigh[j] += 1
    # print(heigh)
    lock_set.add(tuple(heigh))

def solve_1():
    ans = 0
    print(len(key_set), len(lock_set))
    for key in key_set:
        for lock in lock_set:
            flag = True
            for i in range(5):
                if key[i] + lock[i] >= 6:
                    flag = False
            if flag:
                print(key, lock)
                ans += 1
    return ans

if __name__ == "__main__":
    # print(solve_1())
    puzzle.answer_a = solve_1()
