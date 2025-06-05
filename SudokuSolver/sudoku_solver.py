# name: Shuntaro Abe
# student id: 2377370

from sat_solver import solve_sat

# encodes (row, col, val) into a unique variable number (1–729)
def encode_var(r, c, v):
    return 81 * (r - 1) + 9 * (c - 1) + v

# builds the cnf formula for a sudoku grid
def sudoku_encode(grid):
    clauses = []

    # each cell has at least one number, and at most one
    for r in range(1, 10):
        for c in range(1, 10):
            clauses.append([encode_var(r, c, v) for v in range(1, 10)])
            for v1 in range(1, 10):
                for v2 in range(v1 + 1, 10):
                    clauses.append([-encode_var(r, c, v1), -encode_var(r, c, v2)])

    # each number appears once per row
    for r in range(1, 10):
        for v in range(1, 10):
            clauses.append([encode_var(r, c, v) for c in range(1, 10)])
            for c1 in range(1, 10):
                for c2 in range(c1 + 1, 10):
                    clauses.append([-encode_var(r, c1, v), -encode_var(r, c2, v)])

    # each number appears once per column
    for c in range(1, 10):
        for v in range(1, 10):
            clauses.append([encode_var(r, c, v) for r in range(1, 10)])
            for r1 in range(1, 10):
                for r2 in range(r1 + 1, 10):
                    clauses.append([-encode_var(r1, c, v), -encode_var(r2, c, v)])

    # each number appears once per 3x3 block
    for br in range(0, 3):
        for bc in range(0, 3):
            for v in range(1, 10):
                block = []
                for i in range(1, 4):
                    for j in range(1, 4):
                        block.append(encode_var(3 * br + i, 3 * bc + j, v))
                clauses.append(block)
                for i in range(len(block)):
                    for j in range(i + 1, len(block)):
                        clauses.append([-block[i], -block[j]])

    # add clues from the input grid
    for r in range(1, 10):
        for c in range(1, 10):
            v = grid[r - 1][c - 1]
            if v != 0:
                clauses.append([encode_var(r, c, v)])

    return clauses

# solves the sudoku using sat
def solve_sudoku(grid):
    clauses = sudoku_encode(grid)
    assignment = solve_sat(clauses, {})
    if assignment is None:
        return None

    # build solved grid from assignment
    result = [[0 for _ in range(9)] for _ in range(9)]
    for key, val in assignment.items():
        if val:
            k = key - 1
            r, c, v = k // 81 + 1, (k % 81) // 9 + 1, (k % 9) + 1
            result[r - 1][c - 1] = v
    return result
