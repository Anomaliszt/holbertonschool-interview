#!/usr/bin/python3
"""
Module for counting words in Reddit hot articles
"""
import requests


def count_words(subreddit, word_list, after=None, word_count=None,
                word_multiplier=None):
    """
    Recursively queries the Reddit API, parses the title of all hot articles,
    and prints a sorted count of given keywords.

    Args:
        subreddit: The subreddit to query
        word_list: List of keywords to count (case-insensitive)
        after: Parameter for pagination (used in recursion)
        word_count: Dictionary to track word counts (used in recursion)
        word_multiplier: Dictionary to track keyword multipliers for duplicates
    """
    # Initialize word_count dictionary on first call
    if word_count is None:
        word_count = {}
        word_multiplier = {}
        # Normalize word_list to lowercase and count occurrences
        for word in word_list:
            word_lower = word.lower()
            if word_lower not in word_count:
                word_count[word_lower] = 0
                word_multiplier[word_lower] = 0
            word_multiplier[word_lower] += 1

    # Set up the API request
    url = f"https://www.reddit.com/r/{subreddit}/hot.json"
    headers = {'User-Agent': 'python:reddit.word.counter:v1.0 (by /u/student)'}
    params = {'limit': 100}

    if after:
        params['after'] = after

    try:
        # Make the request without following redirects
        response = requests.get(url, headers=headers, params=params,
                                allow_redirects=False)

        # Check if subreddit is invalid (redirect or not found)
        if response.status_code != 200:
            return

        data = response.json()

        # Check if we got valid data
        if 'data' not in data or 'children' not in data['data']:
            return

        posts = data['data']['children']

        # Process each post's title
        for post in posts:
            title = post['data']['title'].lower()
            # Split title into words
            words = title.split()

            for word in words:
                # Strip non-alphanumeric characters
                # This handles cases like "java.", "java!", etc.
                clean_word = ''.join(char for char in word
                                     if char.isalnum())

                # Count the word if it's in our word_count dictionary
                # Multiply by the number of times this keyword appears
                # in word_list
                if clean_word and clean_word in word_count:
                    word_count[clean_word] += word_multiplier[clean_word]

        # Get the 'after' token for pagination
        after = data['data']['after']

        # If there are more pages, recurse
        if after:
            count_words(subreddit, word_list, after, word_count,
                        word_multiplier)
        else:
            # No more pages, print results
            print_results(word_count)

    except Exception:
        # On any error, return silently
        return


def print_results(word_count):
    """
    Print the word count results in descending order by count,
    then alphabetically for same counts.

    Args:
        word_count: Dictionary of word counts
    """
    # Filter out words with zero count
    filtered = {word: count for word, count in word_count.items()
                if count > 0}

    if not filtered:
        return

    # Sort by count (descending) and then alphabetically (ascending)
    sorted_words = sorted(filtered.items(), key=lambda x: (-x[1], x[0]))

    for word, count in sorted_words:
        print(f"{word}: {count}")
