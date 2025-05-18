#!/usr/bin/python3
"""
Reads stdin line by line, computes and prints metrics.
Input format: <IP Address> - [<date>] "GET /260 HTTP/1.1" <status code> <file size>
Metrics are printed after every 10 lines and/or upon a keyboard interruption (CTRL + C).
"""
import sys
import signal
import re

total_file_size = 0
status_code_counts = {}
line_count_since_last_print = 0

POSSIBLE_STATUS_CODES = {200, 301, 400, 401, 403, 404, 405, 500}


LOG_PATTERN = re.compile(
	r'^\S+\s+-\s+\[.*?\]\s+"GET /260 HTTP/1\.1"\s+(\d{3})\s+(\d+)$'
)

def print_statistics():
	"""Prints the accumulated statistics in the required format."""
	print(f"File size: {total_file_size}")
	for code in sorted(status_code_counts.keys()):
		print(f"{code}: {status_code_counts[code]}")
	sys.stdout.flush()

def signal_handler(sig, frame):
	"""
	Handles CTRL+C (SIGINT) interruption.
	Prints statistics and then allows the script to terminate.
	"""
	print_statistics()

signal.signal(signal.SIGINT, signal_handler)

if __name__ == "__main__":
	try:
		for line in sys.stdin:
			line = line.strip()
			match = LOG_PATTERN.match(line)

			if match:
				status_code_str = match.group(1)
				file_size_str = match.group(2)

				try:
					status_code = int(status_code_str)
					file_size = int(file_size_str)

					total_file_size += file_size

					if status_code in POSSIBLE_STATUS_CODES:
						status_code_counts[status_code] = \
							status_code_counts.get(status_code, 0) + 1
					
					line_count_since_last_print += 1

					if line_count_since_last_print >= 10:
						print_statistics()
						line_count_since_last_print = 0

				except ValueError:
					pass

	except KeyboardInterrupt:
		raise
	except Exception:
		raise
