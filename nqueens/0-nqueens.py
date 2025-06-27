#!/usr/bin/python3
"""
N Queens Puzzle Solver
Solves the N Queens problem using backtracking algorithm
"""

import sys


def is_safe(board, row, col, n):
    """
    Check if placing a queen at board[row][col] is safe

    Args:
        board: Current state of the board
        row: Row to place the queen
        col: Column to place the queen
        n: Size of the board

    Returns:
        bool: True if safe, False otherwise
    """
    for i in range(row):
        if board[i] == col:
            return False

    for i in range(row):
        if board[i] == col - (row - i):
            return False

    for i in range(row):
        if board[i] == col + (row - i):
            return False

    return True


def solve_nqueens(board, row, n, solutions):
    """
    Solve N Queens using backtracking

    Args:
        board: Current state of the board (list of column positions)
        row: Current row to place queen
        n: Size of the board
        solutions: List to store all solutions
    """
    if row == n:
        solution = []
        for i in range(n):
            solution.append([i, board[i]])
        solutions.append(solution)
        return

    for col in range(n):
        if is_safe(board, row, col, n):
            board[row] = col
            solve_nqueens(board, row + 1, n, solutions)


def nqueens(n):
    """
    Main function to solve N Queens problem

    Args:
        n: Size of the chessboard (n x n)
    """
    board = [-1] * n
    solutions = []

    solve_nqueens(board, 0, n, solutions)

    for solution in solutions:
        print(solution)


def main():
    """
    Main function to handle command line arguments and run the solver
    """
    if len(sys.argv) != 2:
        print("Usage: nqueens N")
        sys.exit(1)

    try:
        n = int(sys.argv[1])
    except ValueError:
        print("N must be a number")
        sys.exit(1)

    if n < 4:
        print("N must be at least 4")
        sys.exit(1)

    nqueens(n)


if __name__ == "__main__":
    main()
