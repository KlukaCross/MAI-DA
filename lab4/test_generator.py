#! /usr/bin/env python3

import sys
import random
import string

MIN_TEXT_SIZE = 10**3
MAX_TEXT_SIZE = 10**4

MIN_PATTERN_SIZE = 3
MAX_PATTERN_SIZE = 6

MIN_LINE_SIZE = 1
MAX_LINE_SIZE = 32

CHANCE_GEN_PATTERN_EXISTS_VALUE = 0.6  # вероятность при генерации паттерна сгенерить слово, которое уже было в паттерне
CHANCE_GEN_TEXT_EXISTS_VALUE = 0.95  # вероятность при генерации текста сгенерить слово, которое есть в паттерне


def get_random_value():
    str_len = random.randint(1, 5)
    return "".join([random.choice(string.ascii_lowercase) for _ in range(str_len)])


def get_random_exists_value(values):
    return random.choice(values)


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

            buf_text = []
            next_break = random.randint(MIN_LINE_SIZE, MAX_LINE_SIZE)
            lines = 1
            m = random.randint(MIN_TEXT_SIZE, MAX_TEXT_SIZE)
            prev_sum_lines_words = 0
            for i in range(min(n, m)):
                if i == next_break:
                    prev_sum_lines_words = i
                    output_file.write("\n")
                    next_break += random.randint(MIN_LINE_SIZE, MAX_LINE_SIZE)
                    lines += 1

                if random.random() <= CHANCE_GEN_TEXT_EXISTS_VALUE:
                    text = get_random_exists_value(pattern)
                else:
                    text = get_random_value()

                output_file.write(f" {text}")
                buf_text.append(text)

            if pattern == buf_text:
                answer_file.write(f"{lines}, {i-prev_sum_lines_words-n+1}")

            for i in range(n, m):
                if i == next_break:
                    prev_sum_lines_words = i
                    output_file.write("\n")
                    next_break += random.randint(MIN_LINE_SIZE, MAX_LINE_SIZE)
                    lines += 1

                if random.random() <= CHANCE_GEN_TEXT_EXISTS_VALUE:
                    text = get_random_exists_value(pattern)
                else:
                    text = get_random_value()

                output_file.write(f" {text}")
                buf_text.pop(0)
                buf_text.append(text)

                if pattern == buf_text:
                    answer_file.write(f"{lines}, {i-prev_sum_lines_words-n+2}\n")




if __name__ == "__main__":
    main()