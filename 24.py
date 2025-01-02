from aocd.models import Puzzle
from collections import deque

puzzle = Puzzle(2024, 24)

# input = puzzle.input_data
# input = puzzle.examples[0].input_data
with open("./24_input.txt") as f:
    input = f.read()

init_input, operate_input = input.strip().split("\n\n")
init_input = init_input.split('\n')
operate_input = operate_input.split('\n')

def op_simulator(x, y, op):
    if op == "AND":
        return x & y
    if op == "OR":
        return x | y
    if op == "XOR":
        return x ^ y

def solve_1():
    p_val = {}
    for line in init_input:
        key, value = line.strip().split(":")
        p_val[key] = int(value)
    
    Q = deque()
    for line in operate_input:
        p1, op, p2, _, p3 = line.split(' ')
        Q.append((p1, p2, op, p3))

    while Q:
        p1, p2, op, p3 = Q.popleft()
        if p1 not in p_val or p2 not in p_val:
            Q.append((p1, p2, op, p3))
            continue
        p_val[p3] = op_simulator(p_val[p1], p_val[p2], op)

    ans = 0
    mul = 1
    for key in sorted(p_val.keys()):
        if 'z' == key[0]:
            ans += p_val[key] * mul
            mul *= 2
    return ans

def find_next(cur):
    if "z" == cur[0]:
        return cur[:-2] + (str(int(cur[-2:]) - 1) if (int(cur[-2:]) > 10) else '0' + str(int(cur[-2:]) - 1))
    for line in operate_input:
        p1, op, p2, _, p3 = line.split(' ')
        if (p1 == cur or p2 == cur) and op != 'AND':
            return find_next(p3)

def solve_2():
    errors = []
    for line in operate_input:
        p1, op, p2, _, p3 = line.split(' ')
        if p3[0] == 'z'and op != "XOR" and int(p3[1:]) != 45:
            errors.append([p1, op, p2, p3])
            operate_input.remove(line)
        elif 'z' != p3[0] and (p1[0] != 'x' and p2[0] != 'x') and (p1[1] != 'y' and p2[1] != 'y') and op == "XOR":
            errors.append([p1, op, p2, p3])
            operate_input.remove(line)
        elif (p1[0] == 'x' or p2[0] == 'x') and (p1[1] == 'y' or p2[1] == 'y') and op == "OR":
            errors.append([p1, op, p2, p3])
            operate_input.remove(line)
    for i, val in enumerate(errors):
        if val[1] == 'XOR':
            cur = find_next(val[3])
            print(val[3], cur)
            for j, val_2 in enumerate(errors):
                if cur == val_2[3]:
                    errors[i][3], errors[j][3] = errors[j][3], errors[i][3]
    str_list = []
    for val in errors:
        print(val)
        line = val[0] + " " + val[1] + " " + val[2] + " -> " + val[3]
        operate_input.append(line)
        str_list.append(val[3])
    # print(operate_input)
    str_list.append("tnt")
    str_list.append("qmd")
    print(",".join(sorted(str_list)))
    ans_1 = solve_1()

    x_val = ""
    y_val = ""
    for line in init_input:
        key, value = line.strip().split(":")
        if 'x' in key:
            x_val += value.strip()
        elif 'y' in key:
            y_val += value.strip()
    x_val = int(x_val[::-1], 2)
    y_val = int(y_val[::-1], 2)
    ans_2 = x_val + y_val
    ans = ans_1 ^ ans_2
    print(str(bin(ans))[2:])
    print(len(str(bin(ans))[2:]))

                
if __name__ == "__main__":
    # puzzle.answer_a = solve_1()
    solve_2()
    # print(solve_1())
