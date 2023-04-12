#! /usr/bin/env python3

import sys
import random
import string

MIN_OPERATION_COUNT = 10 ** 3
MAX_OPERATION_COUNT = 10 ** 5


def get_random_key():
    str_len = random.randint(1, 256)
    return "".join([random.choice(string.ascii_letters) for _ in range(str_len)])


def get_random_value():
    return random.randint(1, 2 ** 63 - 1)


def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <test dir> <count of tests>")
        sys.exit(1)

    test_dir = sys.argv[1]
    count_of_tests = int(sys.argv[2])

    actions = ["+", "-", "?"]

    for enum in range(count_of_tests):
        keys = dict()
        test_file_name = f"{test_dir}/{enum+1:02d}"
        with open("{0}.t".format(test_file_name), 'w') as output_file, \
                open("{0}.a".format(test_file_name), "w") as answer_file:

            for _ in range(random.randint(MIN_OPERATION_COUNT, MAX_OPERATION_COUNT)):
                action = random.choice(actions)
                exist_element = random.choice([True, False])
                key = random.choice([key for key in keys.keys()]) if exist_element and len(keys.keys()) > 0 else get_random_key()
                if action == "+":
                    value: int = get_random_value()
                    output_file.write(f"+ {key} {value}\n")
                    answer = "Exists"
                    if key.lower() not in keys:
                        answer = "OK"
                        keys[key.lower()] = value
                    answer_file.write(f"{answer}\n")

                elif action == "-":
                    output_file.write("- {0}\n".format(key))
                    answer = "NoSuchWord"
                    if key.lower() in keys:
                        answer = "OK"
                        keys.pop(key.lower())
                    answer_file.write(f"{answer}\n")

                elif action == "?":
                    output_file.write("{0}\n".format(key))
                    answer = "NoSuchWord"
                    if key.lower() in keys:
                        answer = "OK: {0}".format(keys[key.lower()])
                    answer_file.write(f"{answer}\n")


if __name__ == "__main__":
    main()
