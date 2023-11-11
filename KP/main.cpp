#define MINIMP3_IMPLEMENTATION
#include <iostream>
#include <vector>
#include <cmath>
#include <complex>

#include "minimp3.h"
#include "minimp3_ex.h"

typedef std::complex<double> complex;


std::vector<short> decoder() {
    mp3dec_t mp3d;
    mp3dec_file_info_t info;
    if (mp3dec_load(&mp3d, "sample.mp3", &info, NULL, NULL)) {
        throw std::runtime_error("Decode error");
    }
    std::vector<short> res(info.buffer, info.buffer + info.samples);
    free(info.buffer);
    return res;
}

std::vector<complex> hunn(const std::vector<short>& data, size_t start, size_t end) {
    std::vector<complex> res(end-start);
    for (size_t i = start; i < end; ++i) {
        res[i] = 0.5 * (1 - cos(2*M_PI*double(i)/double(end-start))) * data[i];
    }
    return res;
}

void fft(std::vector<complex> & data) {
    size_t n = data.size();
    if (n == 1) return;

    std::vector<complex> a0 (n/2), a1 (n/2);
    for (size_t i=0, j=0; i<n; i+=2, ++j) {
        a0[j] = data[i];
        a1[j] = data[i+1];
    }
    fft (a0);
    fft (a1);

    double ang = 2*M_PI/double(n);
    complex w (1),  wn (cos(ang), sin(ang));
    for (size_t i=0; i<n/2; ++i) {
        data[i] = a0[i] + w * a1[i];
        data[i+n/2] = a0[i] - w * a1[i];
        w *= wn;
    }
}

double getMax(const std::vector<complex>& data) {
    double res = data[0].real();
    for (size_t i = 1; i < data.size(); ++i) {
        if (data[i].real() < res) {
            res = data[i].real();
        }
    }
    return res;
}

int main() {
    std::vector<short> dataIn = decoder();
    size_t n = dataIn.size();
    for (size_t i = 0; i < n; i += 1024) {
        std::vector<complex> transformData = hunn(dataIn, i, (i+4096 < n)? i+4096 : n);
        fft(transformData);
        double answer = getMax(transformData);
        std::cout << answer << '\n';
    }
    return 0;
}
