#!/usr/bin/python3
"""
Module for canUnlockAll method.
"""
import collections


def canUnlockAll(boxes):
    """
    Determines if all the boxes can be opened.

    Args:
        boxes (list of lists): A list where each inner list contains keys
                               to other boxes. box i is boxes[i]

    Returns:
        bool: True if all boxes can be opened, else False
    """
    n = len(boxes)
    if n == 0:
        return True

    opened_boxes = {0}
    queue = collections.deque([0])

    while queue:
        current_box_index = queue.popleft()

        for key in boxes[current_box_index]:
            if 0 <= key < n and key not in opened_boxes:
                opened_boxes.add(key)
                queue.append(key)

    return len(opened_boxes) == n
