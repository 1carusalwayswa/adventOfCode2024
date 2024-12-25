from aocd.models import Puzzle
from collections import deque
from functools import cache

puzzle = Puzzle(2024, 20)
input = puzzle.input_data.split('\n')
# input = puzzle.examples[0].input_data.strip().split('\n')
G = input

def bfs():
    start = [(x, y) for x in range(len(G)) for y in range(len(G[0])) if G[x][y] == 'S'][0]
    Q = deque([(*start, 0)])
    dir = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    vis = {start}

    rows, cols = len(G), len(G[0])
    dis = [[0] * cols for _ in range(rows)]

    while Q:
        x, y, cost = Q.popleft()
        dis[x][y] = cost

        if G[x][y] == 'E':
            return vis, dis, cost
        
        for dx, dy in dir:
            tx = x + dx
            ty = y + dy
            if tx >= 0 and tx < rows and ty >= 0 and ty < cols and (G[tx][ty] != '#') and (tx, ty) not in vis:
                vis.add((tx, ty))
                Q.append((tx, ty, cost + 1))

vis = []
dis = []

def judge_valid(x, y):
    dir = [(1, 0), (-1, 0), (0, 1), (0, -1)]

    reach_loc = []
    for dx, dy in dir:
        tx = x + dx
        ty = y + dy
        if (tx, ty) in vis:
            reach_loc.append((tx, ty))

    return reach_loc

def solve_1():
    obstacles = [(x, y) for x in range(len(G)) for y in range(len(G[0])) if (G[x][y] == '#')]
    # print(len(obstacles))
    cnt1 = 0
    # single
    ans = []
    for x, y in obstacles:
        reach_loc = judge_valid(x, y)
        if len(reach_loc) > 0:
            max_dis = 0
            for i in range(len(reach_loc)):
                for j in range(i + 1, len(reach_loc)):
                    x1, y1 = reach_loc[i]
                    x2, y2 = reach_loc[j]
                    max_dis = max(max_dis, abs(dis[x1][y1] - dis[x2][y2]) - 2)
            if max_dis >= 100:
                cnt1 += 1
    print(cnt1)
    return cnt1

vis_end = set()
@cache
def dfs(x, y, res, cost, limit):
    if res == 0:
        if G[x][y] == '#':
            return 0
        if (x, y) in vis_end:
            return 0
        if (dis[x][y] - cost) >= limit:
            vis_end.add((x, y))
            return 1
        else:
            return 0
    dir = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    rows, cols = len(G), len(G[0])
    for dx, dy in dir:
        tx = x + dx
        ty = y + dy
        if tx >= 0 and tx < rows and ty >= 0 and ty < cols:
            dfs(tx, ty, res - 1, cost + 1, limit)
    if G[x][y] != '#' and (dis[x][y] - cost) >= limit and (x, y) not in vis_end:
        vis_end.add((x, y))
    return len(vis_end)

def solve_2(step, limit):
    cnt = 0
    for x in range(len(G)):
        for y in range(len(G[0])):
            if G[x][y] == '#':
                continue
            vis_end.clear()
            ans = dfs(x, y, step, dis[x][y], limit)
            if ans > 0:
                cnt += ans
    return cnt
    

if __name__ == "__main__":
    vis, dis, standard_path  = bfs()
    # p1 = solve_1()
    # print(solve_2(20, 100))
    puzzle.answer_a = solve_2(2, 100)
    puzzle.answer_b = int(solve_2(20, 100))
    # print(solve_2(20, 100) == 1000697)
        
        

