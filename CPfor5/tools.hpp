#ifndef CPFOR5_TOOLS_HPP
#define CPFOR5_TOOLS_HPP

#include <vector>
#include <complex>

typedef std::complex<double> complex;
const std::vector<short> FREQUENCY_RANGES {40, 80, 120, 180, 300};

typedef std::complex<double> complex;

std::vector<uint64_t> calculateHashes(const std::vector<short>& data);

uint64_t hash(const std::vector<short>& frequency);

size_t getFrequencyIndex(short frequency);

std::vector<short> decoder(const std::string& filename);

#endif //CPFOR5_TOOLS_HPP
