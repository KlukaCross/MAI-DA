#include <iostream>
#include <unordered_set>
#include "audiosearch.hpp"

#include "tools.hpp"

const double MINIMAL_COINCIDENCE_NUMBER = 5;

uint32_t diff(uint32_t a, uint32_t b) {
    return (a > b) ? a - b : b - a;
}

std::string Audiosearch::search(const std::string &filename) {

    std::vector<short> data;
    try {
        data = decoder(filename.data());
    } catch (std::runtime_error& err) {
        std::cout << filename << " - " << err.what() << "\n";
        return "! NOT FOUND";
    }

    std::vector<uint64_t> hashes = calculateHashes(data);

    std::unordered_map<uint32_t, uint32_t> statistics;
    uint64_t counter = 0;
    for (uint32_t i = 0; i < hashes.size(); ++i) {
        for (uint32_t j = i + 1; j < hashes.size(); ++j) {
            uint64_t firstHash = hashes[i], secondHash = hashes[j];
            std::vector<Entry> firstVector = db->findEntry(firstHash);
            std::vector<Entry> secondVector = db->findEntry(secondHash);
            if (firstVector.empty() || secondVector.empty())
                continue;

            for (const Entry &firstEntry: firstVector) {
                for (const Entry &secondEntry: secondVector) {
                    if (firstEntry.musicId == secondEntry.musicId && diff(i, j) == diff(firstEntry.timeBlock, secondEntry.timeBlock)) {
                        ++statistics[firstEntry.musicId];
                        ++counter;
                    }
                }
            }
        }
    }
    if (counter == 0)
        return "! NOT FOUND";

    std::vector<std::pair<std::string, double>> statisticsInPercent;
    statisticsInPercent.reserve(statistics.size());
    for (const auto &[id, stat]: statistics) {
        statisticsInPercent.emplace_back(db->getMusic(id), stat);
    }
    std::sort(statisticsInPercent.begin(), statisticsInPercent.end(), [](const auto &left, const auto &right) { return left.second > right.second; });
    if (statisticsInPercent[0].second < MINIMAL_COINCIDENCE_NUMBER)
        return "! NOT FOUND";

    for (auto &pair: statisticsInPercent) {
        pair.second = pair.second / double(counter) * 100.;
    }
    return statisticsInPercent[0].first;
}
