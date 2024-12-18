from aocd.models import Puzzle
from collections import deque
import time

def solve(input, limit_cnt):
    cnt = 0

    obstacles = []
    for line in input:
        cnt += 1
        if cnt > limit_cnt:
            break
        y, x = map(int, line.split(','))
        obstacles.append([x, y])

    grid = [['.' for _ in range(71)] for _ in range(71)]
    for ob in obstacles:
        x, y = ob
        grid[x][y] = '#'

    rows, cols = len(grid), len(grid[0])
    dir = [(-1, 0), (1, 0), (0, 1), (0, -1)]
    que = deque([(0, 0, 0)])
    vis = {(0, 0)}

    output_grid = []
    for row in grid:
        output_grid.append(list(row))

    while que:
        row, col, dist = que.popleft()
        output_grid[row][col] = 'O'

        if row == rows - 1 and col == cols - 1:
            # for row in output_grid:
            #     print(''.join(row))
            return dist
        
        for dx, dy in dir:
            tx, ty = row + dx, col + dy

            if (0 <= tx < rows and 0 <= ty < cols and grid[tx][ty] != '#' and (tx, ty) not in vis):
                que.append((tx, ty, dist + 1))
                vis.add((tx, ty))
    
    # for row in output_grid:
    #     print(''.join(row))

    return -1

def solve_2(input):
    max_cnt = len(input)

    cnt = 0
    for line in input:
        cnt += 1
        if solve(input, cnt) == -1:
            return line
        
def solve_2_faster(input):
    max_cnt = len(input)

    ans_idx = max_cnt
    cnt = 1
    while cnt <= max_cnt:
        if solve(input, cnt) != -1:
            cnt *= 2
        else:
            ans_idx = min(ans_idx, cnt)
            cnt /= 2

if __name__ == "__main__":
    puzzle = Puzzle(2024, 18)
    input = puzzle.input_data.split('\n')

    p1 = solve(input, 1024)
    puzzle.answer_a = p1
    start_time = time.time()
    p2 = solve_2(input)
    end_time = time.time()
    print(end_time - start_time)
    puzzle.answer_b = p2



