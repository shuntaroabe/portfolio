from sat_solver import solve_sat

def test_sat():
    tests = [
        (
            [[1, 2], [-1], [-2], [-1, -2]],
            {},
            None
        ),
        (
            [[1, 2], [-1], [2]],
            {},
            {1: False, 2: True}
        ),
        (
            [[1], [2], [3], [-4], [-5], [-6]],
            {},
            {1: True, 2: True, 3: True, 4: False, 5: False, 6: False}
        ),
        (
            [[1, -2], [-1, 2], [3], [-3, 4], [-4]],
            {},
            None
        ),
    ]

    for i, (clauses, assignment, expected) in enumerate(tests, 1):
        result = solve_sat(clauses, assignment.copy())
        print(f"Test {i}:")
        print(f"  Clauses: {clauses}")
        print(f"  Expected: {expected}")
        print(f"  Got:      {result}")
        print(f"  Pass:     {result == expected}")
        print()

test_sat()
