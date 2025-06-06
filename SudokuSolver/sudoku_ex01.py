from sudoku_solver import solve_sudoku

def print_grid(grid):
    if grid is None:
        print("None")
    else:
        for row in grid:
            print(row)

def main():
    test_cases = [
        [
            [5, 3, 0, 0, 7, 0, 0, 0, 0],
            [6, 0, 0, 1, 9, 5, 0, 0, 0],
            [0, 9, 8, 0, 0, 0, 0, 6, 0],
            [8, 0, 0, 0, 6, 0, 0, 0, 3],
            [4, 0, 0, 8, 0, 3, 0, 0, 1],
            [7, 0, 0, 0, 2, 0, 0, 0, 6],
            [0, 6, 0, 0, 0, 0, 2, 8, 0],
            [0, 0, 0, 4, 1, 9, 0, 0, 5],
            [0, 0, 0, 0, 8, 0, 0, 7, 9],
        ],
        [
            [0, 0, 0, 0, 0, 1, 2, 0, 3],
            [0]*9,
            [0]*9,
            [0]*9,
            [0]*9,
            [0]*9,
            [0]*9,
            [0]*9,
            [0]*9,
        ],
        [
            [1,1,0,0,0,0,0,0,0],
            [0]*9,
            [0]*9,
            [0]*9,
            [0]*9,
            [0]*9,
            [0]*9,
            [0]*9,
            [0]*9,
        ],
        [
            [1,0,0,0,0,0,0,0,0],
            [0,1,0,0,0,0,0,0,0],
            [0,0,1,0,0,0,0,0,0],
            [0,0,0,1,0,0,0,0,0],
            [0,0,0,0,1,0,0,0,0],
            [0,0,0,0,0,1,0,0,0],
            [0,0,0,0,0,0,1,0,0],
            [0,0,0,0,0,0,0,1,0],
            [0,0,0,0,0,0,0,0,1],
        ],
        [
            [5, 1, 6, 8, 4, 9, 7, 3, 2],
            [3, 0, 7, 6, 0, 5, 0, 0, 0],
            [8, 0, 9, 7, 0, 0, 0, 6, 5],
            [1, 3, 5, 0, 6, 0, 9, 0, 7],
            [4, 7, 2, 5, 9, 1, 0, 0, 6],
            [9, 6, 8, 3, 7, 0, 0, 5, 0],
            [2, 5, 3, 1, 8, 6, 0, 7, 4],
            [6, 8, 4, 2, 0, 7, 5, 0, 0],
            [7, 9, 1, 0, 5, 0, 6, 0, 8],
        ]
    ]

    for i, puzzle in enumerate(test_cases, 1):
        print(f"\n--- Test Case #{i} ---")
        result = solve_sudoku(puzzle)
        print_grid(result)

if __name__ == "__main__":
    main()
