#! /usr/bin/env python3

import random
import sys
from string import ascii_lowercase


def gen_random_value(size: int) -> str:
    return "".join([random.choice(ascii_lowercase) for _ in range(size)])


def get_answer(value: str) -> str:
    min_sector = value
    for i in range(len(value)):
        tmp = value[i:]+value[:i]
        min_sector = min(min_sector, tmp)
    return min_sector


def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <test dir> <count of tests>")
        sys.exit(1)

    test_dir = sys.argv[1]
    count_of_tests = int(sys.argv[2])

    for i in range(count_of_tests):
        random_value = gen_random_value(10**i)
        answer = get_answer(random_value)

        test_file_name = f"{test_dir}/{i+1:02d}"
        with open("{0}.t".format(test_file_name), 'w') as output_file, \
                open("{0}.a".format(test_file_name), "w") as answer_file:
            output_file.write(random_value + '\n')
            answer_file.write(answer + '\n')


main()
