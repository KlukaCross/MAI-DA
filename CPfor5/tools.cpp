#define MINIMP3_IMPLEMENTATION
#include "tools.hpp"

#include "minimp3.h"
#include "minimp3_ex.h"

const size_t WINDOW_SIZE = 4096, WINDOW_STEP = 1024;

std::vector<complex> hunn(const std::vector<short>& data, size_t start, size_t end) {
    std::vector<complex> res(end-start);
    for (size_t i = start; i < end; ++i) {
        res[i-start] = data[i] * 0.5 * (1 - cos(2*M_PI*double(i-start)/double(end-start-1)));
    }
    return res;
}

void fft(std::vector<complex> & data) {
    size_t n = data.size();
    if (n == 1) return;

    std::vector<complex> even (n / 2), odd (n / 2);
    for (size_t i=0; i<n/2; ++i) {
        even[i] = data[2*i];
        odd[i] = data[2*i + 1];
    }
    fft (even);
    fft (odd);

    double ang = 2*M_PI/double(n);
    complex w (1),  wn (cos(ang), sin(ang));
    for (size_t i=0; i<n/2; ++i) {
        data[i] = even[i] + w * odd[i];
        data[i+n/2] = even[i] - w * odd[i];
        w *= wn;
    }
}

uint64_t hash(const std::vector<short>& frequency) {
    uint64_t res = 0;
    for (size_t i = 0; i < frequency.size(); ++i) {
        res += frequency[i] * std::pow(1000, i);
    }
    return res;
}

size_t getFrequencyIndex(short frequency) {
    size_t i = 0;
    while (FREQUENCY_RANGES[i] < frequency)
        ++i;
    return i;
}

std::vector<uint64_t> calculateHashes(const std::vector<short>& data) {
    std::vector<uint64_t> result;
    size_t n = data.size();
    size_t freq_ranges_size = FREQUENCY_RANGES.size();
    for (size_t i = 0; i+WINDOW_SIZE < n; i += WINDOW_STEP) {
        std::vector<complex> transformData = hunn(data, i, i + WINDOW_SIZE);
        fft(transformData);
        std::vector<short> maxFrequency(freq_ranges_size, 0);
        std::vector<double> maxPower(freq_ranges_size, -1);
        for (short freq = FREQUENCY_RANGES[0]; freq < FREQUENCY_RANGES[freq_ranges_size-1]; ++freq) {
            double power = std::abs(transformData[freq]);
            size_t index = getFrequencyIndex(freq);
            if (power > maxPower[index]) {
                maxPower[index] = power;
                maxFrequency[index] = freq;
            }
        }
        result.emplace_back(hash(maxFrequency));
    }
    return result;
}

std::vector<short> decoder(const std::string &filename) {
    mp3dec_t mp3d;
    mp3dec_file_info_t info;
    if (mp3dec_load(&mp3d, filename.data(), &info, NULL, NULL)) {
        throw std::runtime_error("Decode error");
    }
    std::vector<short> res(info.buffer, info.buffer + info.samples);
    free(info.buffer);
    return res;
}