# There is a more easier way to use networkx.find_cliques (why does everyone knows that?)
from aocd.models import Puzzle
from collections import defaultdict
import sys

puzzle = Puzzle(2024, 23)
input = puzzle.input_data.split('\n')
# input = puzzle.examples[0].input_data.split('\n')

g = defaultdict(set)
for line in input:
    st, ed = line.split('-')
    g[st].add(ed)
    g[ed].add(st)

def solve_1():
    ans = 0
    elements = set()
    for st in g:
        g_list = list(g[st])
        for i in range(len(g_list)):
            mid = g_list[i]
            for j in range(i + 1, len(g_list)):
                ed = g_list[j]
                if ed in g[mid]:
                    if 't' == st[0] or 't' == mid[0] or 't' == ed[0]:
                        ans += 1
                        # element = tuple(sorted([st, mid, ed]))
                        # elements.add(element)
                        # print(st, mid, ed)
    # elements = sorted(list(elements))
    # for ele in elements:
    #     print(", ".join(ele))
    return ans // 3

def bron_kerbosch_with_pivot(R, P, X, graph, cliques):
    if not P and not X:
        cliques.append(R)
        return
    u = max(P.union(X), key=lambda vertex: len(graph[vertex]))
    for v in P - set(graph[u]):
        bron_kerbosch_with_pivot(R.union([v]), P.intersection(graph[v]), X.intersection(graph[v]), graph, cliques)
        P.remove(v)
        X.add(v)

def find_max_clique(graph):
    cliques = []
    bron_kerbosch_with_pivot(set(), set(graph.keys()), set(), graph, cliques)
    max_clique = max(cliques, key=len)
    return max_clique

def solve_2():
    max_clique = find_max_clique(g)
    return ",".join(sorted(max_clique))

if __name__ == "__main__":
    # with open('23_output.txt', 'w') as f:
    #     sys.stdout = f
    ans2 = solve_2()
    ans = solve_1()
    # print(ans)
    puzzle.answer_a = ans
    # print(ans2)
    puzzle.answer_b = ans2
