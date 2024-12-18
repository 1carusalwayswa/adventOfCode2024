'''
a very cool and elegent solution for part_2, but don't come up with it by me (Thx, Emil Segerbäck).
It solves part2 by generating base on sequence rather than brute force.
I thought I may need find some ways to narrow the search range, but my best try only 
find a range(2^45, 2^48), it stills very large.
I trid to base on sequence to deduce the input, but there is some step can not be dedeced straight.
'''

from aocd.models import Puzzle
import re

def solve_1(registers, program_pairs):
    instruction_pointer = 0
    literal_oprands = [0, 1, 2, 3, 4, 5, 6, 7]
    combo_oprands = [0, 1, 2, 3, 'A', 'B', 'C', 7]
    ans = ""
    while instruction_pointer < len(program_pairs):
        op, oprand = program_pairs[instruction_pointer]
        if op == 0:
            registers['A'] = registers['A'] // 2 ** registers[combo_oprands[oprand]]
        elif op == 1:
            registers['B'] = registers['B'] ^ literal_oprands[oprand]
        elif op == 2:
            registers['B'] = registers[combo_oprands[oprand]] % 8
        elif op == 3:
            if registers['A'] != 0:
                instruction_pointer = oprand
                continue
        elif op == 4:
            registers['B'] = registers['B'] ^ registers['C']
        elif op == 5:
            if ans != "":
                ans += ","
            ans += str(registers[combo_oprands[oprand]] % 8)
        elif op == 6:
            registers['B'] = registers['A'] // 2 ** registers[combo_oprands[oprand]]
        elif op == 7:
            registers['C'] = registers['A'] // 2 ** registers[combo_oprands[oprand]] 
        
        instruction_pointer += 1
    
    return ans

def solve_2(last_a, program):
    if not program:
        yield last_a
    else:
        for i in range(8):
            a = (last_a << 3) | i
            b = (a >> ((a % 8) ^ 5)) ^ (a % 8) ^ 5 ^ 6
            if b % 8 == program[-1]:
                yield from solve_2(a, program[:-1])

if __name__ == "__main__":
    puzzle = Puzzle(2024, 17)
    input = puzzle.input_data.split('\n')

    # with open('17_input.txt', 'r') as file:
    #     input = file.read().strip().split('\n')

    registers = {}
    program = {}

    for line in input:
        if line.startswith("Register"):
            match = re.match(r"Register (\w): (\d+)", line)
            if match:
                registers[match.group(1)] = int(match.group(2))
        elif line.startswith("Program"):
            program = list(map(int, re.findall(r"\d+", line)))
    
    for i  in range(0 ,4):
        registers[i] = i
    registers[7] = 7

    program_pairs = [(program[i], program[i + 1]) for i in range(0, len(program), 2)]
    p1 = solve_1(registers, program_pairs)
    p2 = min(list(solve_2(0, program))) 
    puzzle.answers = [p1, p2]