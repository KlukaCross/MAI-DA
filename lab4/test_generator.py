#! /usr/bin/env python3

import sys
import random
import string

MIN_TEXT_SIZE = 10**6
MAX_TEXT_SIZE = 10**6

MIN_PATTERN_SIZE = 64
MAX_PATTERN_SIZE = 64

MIN_LINE_SIZE = 64
MAX_LINE_SIZE = 128

CHANCE_GEN_PATTERN_EXISTS_VALUE = 0.3  # вероятность при генерации паттерна сгенерить слово, которое уже было в паттерне
CHANCE_GEN_TEXT_EXISTS_VALUE = 0.6  # вероятность при генерации текста сгенерить слово, которое есть в паттерне


def get_random_value():
    str_len = random.randint(1, 5)
    return "".join([random.choice(string.ascii_lowercase) for _ in range(str_len)])


def get_random_exists_value(values):
    return random.choice(values)


def get_line_pos(lines_info, i_in_line, n):
    if i_in_line > n:
        return lines_info[-1][0], i_in_line-n
    n -= i_in_line
    i = len(lines_info)-1
    while lines_info[i][1] < n:
        n -= lines_info[i][1]
    return lines_info[i][0], lines_info[i][0]-n

def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <test dir> <count of tests>")
        sys.exit(1)

    test_dir = sys.argv[1]
    count_of_tests = int(sys.argv[2])

    n = random.randint(MIN_PATTERN_SIZE, MAX_PATTERN_SIZE)

    pattern = []
    for i in range(n):
        if i > 0 and random.random() <= CHANCE_GEN_PATTERN_EXISTS_VALUE:
            pattern.append(get_random_exists_value(pattern))
        else:
            pattern.append(get_random_value())

    for enum in range(count_of_tests):

        test_file_name = f"{test_dir}/{enum+1:02d}"
        with open("{0}.t".format(test_file_name), 'w') as output_file, \
                open("{0}.a".format(test_file_name), "w") as answer_file:
            output_file.write(f"{' '.join(pattern)}\n")

            next_break = random.randint(MIN_LINE_SIZE, MAX_LINE_SIZE)
            m = random.randint(MIN_TEXT_SIZE, MAX_TEXT_SIZE)
            for i in range(min(n, m)):
                if i == next_break:
                    output_file.write("\n")
                    next_break += random.randint(MIN_LINE_SIZE, MAX_LINE_SIZE)

                if random.random() <= CHANCE_GEN_TEXT_EXISTS_VALUE:
                    text = get_random_exists_value(pattern)
                else:
                    text = get_random_value()

                output_file.write(f" {text}")

            for i in range(n, m):
                if i == next_break:
                    output_file.write("\n")
                    next_break += random.randint(MIN_LINE_SIZE, MAX_LINE_SIZE)

                if random.random() <= CHANCE_GEN_TEXT_EXISTS_VALUE:
                    text = get_random_exists_value(pattern)
                else:
                    text = get_random_value()

                output_file.write(f" {text}")


if __name__ == "__main__":
    main()