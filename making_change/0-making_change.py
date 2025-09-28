#!/usr/bin/python3
"""
Making Change - Coin Change Problem
Given a pile of coins of different values, determine the fewest number
of coins needed to meet a given amount total.
"""


def makeChange(coins, total):
    """
    Determine the fewest number of coins needed to meet a given amount total.

    Args:
        coins (list): List of coin values (integers > 0)
        total (int): Target amount

    Returns:
        int: Fewest number of coins needed to meet total
             0 if total is 0 or less
             -1 if total cannot be met by any number of coins
    """
    if total <= 0:
        return 0

    dp = [float('inf')] * (total + 1)
    dp[0] = 0

    for amount in range(1, total + 1):
        for coin in coins:
            if coin <= amount:
                dp[amount] = min(dp[amount], dp[amount - coin] + 1)

    return dp[total] if dp[total] != float('inf') else -1
