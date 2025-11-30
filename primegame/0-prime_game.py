#!/usr/bin/python3
"""
Prime Game
"""


def isWinner(x, nums):
    """
    Determines the winner of the Prime Game
    """
    if x < 1 or not nums:
        return None

    maria_wins = 0
    ben_wins = 0

    n = max(nums)
    primes = [True for _ in range(max(n + 1, 2))]
    primes[0], primes[1] = False, False

    for i in range(2, int(n**0.5) + 1):
        if primes[i]:
            for j in range(i*i, n + 1, i):
                primes[j] = False

    primes_count = [0] * (max(n + 1, 2))
    c = 0
    for i in range(len(primes)):
        if primes[i]:
            c += 1
        primes_count[i] = c

    for i in range(x):
        if i < len(nums):
            if primes_count[nums[i]] % 2 == 1:
                maria_wins += 1
            else:
                ben_wins += 1
        else:
            break

    if maria_wins > ben_wins:
        return "Maria"
    elif ben_wins > maria_wins:
        return "Ben"
    else:
        return None
