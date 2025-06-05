# name: Shuntaro Abe
# student id: 2377370

# sat solver using unit propagation + backtracking
# clauses: list of lists (cnf), assignment: dict of current variable values

def solve_sat(clauses, assignment):
    # convert all clauses to sets for easier checks
    clauses = [set(clause) for clause in clauses]

    # unit propagation loop
    while True:
        unit_clauses = [c for c in clauses if len(c) == 1]
        if not unit_clauses:
            break
        for clause in unit_clauses:
            lit = next(iter(clause))
            var = abs(lit)
            val = lit > 0

            # conflict with current assignment
            if var in assignment and assignment[var] != val:
                return None

            # set value and simplify clauses
            assignment[var] = val
            new_clauses = []
            for c in clauses:
                if lit in c:
                    continue  # clause satisfied
                if -lit in c:
                    c = c.copy()
                    c.remove(-lit)  # remove false literal
                new_clauses.append(c)
            clauses = new_clauses

    # success if all clauses are satisfied
    if not clauses:
        return assignment

    # failure if any clause is empty
    if any(c == set() for c in clauses):
        return None

    # pick unassigned variable and try both true/false
    for clause in clauses:
        for lit in clause:
            var = abs(lit)
            if var not in assignment:
                for val in [True, False]:
                    new_assignment = assignment.copy()
                    new_assignment[var] = val
                    result = solve_sat(clauses + [{var if val else -var}], new_assignment)
                    if result is not None:
                        return result
                return None  # neither value worked

    return assignment
