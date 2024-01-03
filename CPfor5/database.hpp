#ifndef CPFOR5_DATABASE_HPP
#define CPFOR5_DATABASE_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

const size_t FILENAME_LIMIT_SIZE = 256;

struct Entry {
    uint32_t timeBlock;
    uint32_t musicId;

    Entry(uint32_t block, uint32_t musicId) : timeBlock(block), musicId(musicId) {};
};

class Database {
private:
    std::unordered_map<uint64_t, std::vector<Entry>> database;
    std::vector<std::string> musicNames;
public:
    void loadFromNamesFile(const std::string &filename);
    void loadFromIndexFile(const std::string &filename);
    void saveToFile(const std::string &filename);
    std::vector<Entry> findEntry(uint64_t hash);
    std::string getMusic(uint32_t musicId);
};


#endif //CPFOR5_DATABASE_HPP
