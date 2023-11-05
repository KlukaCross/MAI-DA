#include <iostream>
#include <vector>

std::vector<uint32_t> coinExchange(std::vector<uint64_t>& nominal, uint32_t m) {
    std::vector<uint32_t> answer(nominal.size());
    for (size_t i = nominal.size() - 1; m > 0; --i) {
        answer[i] = m / nominal[i];
        m -= answer[i] * nominal[i];
    }
    return answer;
}
