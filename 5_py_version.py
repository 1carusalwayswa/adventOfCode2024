import functools

def solve(path):
    rule = set()
    updates = []
    with open(path) as f:
        itr = iter(f)
        for line in itr:
            if "|" not in line:
                break

            l, r = line.strip().split("|")
            rule.add((int(l), int(r)))

        for line in itr:
            updates.append([int(x) for x in line.strip().split(",")])

    res = 0
    def cmp(left, right):
        if (left, right) in rule:
            return -1
        if (right, left) in rule:
            return 1
        return 0
    
    for update in updates:
        indices = {v:i for i, v in enumerate(update)}
        correct = not any (
            left in indices and right in indices and indices[left] > indices[right]
            for left, right in rule
        )

        if not correct:
            update.sort(key=functools.cmp_to_key(cmp))
            res += update[len(update) // 2]

    return res

if __name__ == "__main__":
    ans = solve("/Users/lyon/Desktop/TDDD38/adventOfCode2024/5_input.txt")
    print(ans)
