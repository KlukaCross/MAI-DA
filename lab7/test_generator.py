#! /usr/bin/env python3

import random
import sys
import itertools


def gen_random_pair() -> tuple[int, int]:
    return random.randint(1, 100), random.randint(1, 100)


def get_answer(n, m, pairs) -> tuple[int, list[int]]:
    indexes = range(n)
    indexes_subsets = itertools.chain.from_iterable(itertools.combinations(indexes, r) for r in range(n+1))
    max_answer = 0
    max_subset = []
    for ss in indexes_subsets:
        tmp_c = 0
        tmp_w = 0
        for ind in ss:
            tmp_c += pairs[ind][1]
            tmp_w += pairs[ind][0]
        if tmp_w > m:
            continue
        elif tmp_c*len(ss) > max_answer:
            max_answer = tmp_c*len(ss)
            max_subset = ss
    return max_answer, max_subset


def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <test dir> <count of tests>")
        sys.exit(1)

    test_dir = sys.argv[1]
    count_of_tests = int(sys.argv[2])

    for i in range(10*count_of_tests):
        n, m = random.randint(1, 10), random.randint(1, 100)
        pairs = [gen_random_pair() for _ in range(n)]
        max_count, indexes = get_answer(n, m, pairs)

        test_file_name = f"{test_dir}/{i+1:02d}"
        with open("{0}.t".format(test_file_name), 'w') as output_file, \
                open("{0}.a".format(test_file_name), "w") as answer_file:
            output_file.write(f"{n} {m}\n")
            for w, c in pairs:
                output_file.write(f"{w} {c}\n")
            answer_file.write(f"{max_count}\n")
            for ind in indexes:
                answer_file.write(f"{ind+1} ")
            answer_file.write('\n')


main()
