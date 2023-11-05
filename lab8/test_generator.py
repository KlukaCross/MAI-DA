#! /usr/bin/env python3

import random
import sys


def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <test dir> <count of tests>")
        sys.exit(1)

    test_dir = sys.argv[1]
    count_of_tests = int(sys.argv[2])

    for i in range(count_of_tests):
        n, p, m = random.randint(2, 10), random.randint(2, 100), random.randint(1, 2**32-1)
        nominals = [p**i for i in range(n)]
        answer = [0]*n
        j = n-1
        m_copy = m
        while m_copy > 0:
            answer[j] = m_copy // nominals[j]
            m_copy -= answer[j] * nominals[j]
            j -= 1

        test_file_name = f"{test_dir}/{i+1:02d}"
        with open("{0}.t".format(test_file_name), 'w') as output_file, \
                open("{0}.a".format(test_file_name), "w") as answer_file:
            output_file.write(f"{n} {p}\n{m}")
            for number in answer:
                answer_file.write(f"{number}\n")

main()
