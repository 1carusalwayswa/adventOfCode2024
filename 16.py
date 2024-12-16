# first time only py version, due to use cpp to solve is too complicated.
# learn from https://github.com/badboj40/advent-of-code/blob/master/2024/16.py
from aocd.models import Puzzle
import heapq

def best_seats(goals, prevs):
    on_path = set()
    for goal in goals:
        seats = {goal}
        while seats:
            cur = seats.pop()
            if not cur:
                continue
            on_path.add((cur[0], cur[1]))
            seats |= prevs[cur]
    return len(on_path)


def explore(G, start):
    Q = [(0, (*start, 0, 1), None)]
    vis = {}
    prevs = {}
    goals = set()
    best = float("inf")

    while Q:
        score, cur, prev = heapq.heappop(Q)
        x, y, dx, dy = cur
        if G[x][y] == '#' or score > min(best, vis.get(cur, float("inf"))) :
            continue

        # print(str(cur) + " " + str(score))
        prevs[cur] = prevs.get(cur, set()) | {prev}
        vis[cur] = score

        if G[x][y] == "E":
            goals.add(cur)
            best = min(best, score)
            continue

        heapq.heappush(Q, (score + 1000, (x, y, -dy, dx), cur))
        heapq.heappush(Q, (score + 1000, (x, y, dy, -dx), cur))
        heapq.heappush(Q, (score + 1, (x + dx, y + dy, dx, dy), cur))
    return best, best_seats(goals, prevs)



if __name__ == "__main__":
    G = Puzzle(2024, 16).input_data.split('\n')
    start = [(x, y) for x in range(len(G)) for y in range(len(G[0])) if G[x][y] == "S"][0]
    p1, p2 = explore(G, start)
    print(p1, " ", p2)
