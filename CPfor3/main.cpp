#define MINIMP3_IMPLEMENTATION
#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>
#include <complex>

#include "minimp3.h"
#include "minimp3_ex.h"

typedef std::complex<double> complex;
const size_t WINDOW_SIZE = 4096, WINDOW_STEP = 1024;

std::vector<short> decoder(const std::string& filename) {
    mp3dec_t mp3d;
    mp3dec_file_info_t info;
    if (mp3dec_load(&mp3d, filename.data(), &info, NULL, NULL)) {
        throw std::runtime_error("Decode error");
    }
    std::vector<short> res(info.buffer, info.buffer + info.samples);
    free(info.buffer);
    return res;
}

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

double getMax(const std::vector<complex>& data) {
    double res = abs(data[0]);
    for (size_t i = 1; i < data.size(); ++i) {
        if (abs(data[i]) > res) {
            res = abs(data[i]);
        }
    }
    return res;
}


int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string filename;
    if (argc == 1) {
        filename = "input.mp3";
    } else if (argc == 2) {
        filename = argv[1];
    } else {
        std::cout << "usage: " << argv[0] << "[filename]\n";
        return 1;
    }
    std::vector<short> dataIn = decoder(filename);

    size_t n = dataIn.size();
    for (size_t i = 0; i+WINDOW_SIZE < n; i += WINDOW_STEP) {
        std::vector<complex> transformData = hunn(dataIn, i, i+WINDOW_SIZE);
        fft(transformData);
        double answer = getMax(transformData);
        std::cout << std::setprecision(26) << answer << '\n';
    }
    return 0;
}
