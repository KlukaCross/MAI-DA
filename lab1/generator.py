import sys
import random
import string
import secrets

TEST_COUNT = 6
MIN_STRING_SIZE = 0
MAX_STRING_SIZE = 64
NUMBER_SIZE = 32


def get_random_string():
    length = random.randint(MIN_STRING_SIZE, MAX_STRING_SIZE)
    random_list = [random.choice(string.ascii_lowercase) for _ in range(length)]
    return "".join(random_list)


def get_random_number():
    return secrets.token_hex(NUMBER_SIZE//2)


def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <test directory>")
        sys.exit(1)

    test_dir = sys.argv[1]

    lines = [0]
    lines.extend([10 ** i for i in range(TEST_COUNT)])

    for enum, test_count in enumerate(range(1, TEST_COUNT+1)):
        test = []

        line_count = lines[enum]
        for _ in range(line_count):
            key = get_random_number()
            value = get_random_string()
            test.append((key, value))

        test_name = "{}/{:02d}".format(test_dir, test_count)
        with open(f'{test_name}.t', 'w') as ftest:
            for key, value in test:
                ftest.write(f'{key}\t{value}\n')

        answer = sorted(test, key=lambda x: x[0])
        with open(f'{test_name}.a', 'w') as ftest:
            for key, value in answer:
                ftest.write(f'{key}\t{value}\n')

main()

