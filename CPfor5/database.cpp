#include <stdexcept>
#include <fstream>
#include <iostream>
#include <filesystem>

#include "database.hpp"

#include "tools.hpp"


void Database::loadFromNamesFile(const std::string &filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cout << filename << " - File open error\n";
        return;
    }
    char buff[FILENAME_LIMIT_SIZE];
    while (!fin.eof()) {
        fin.getline(buff, FILENAME_LIMIT_SIZE);
        if (buff[0] == '\0')
            break;
        std::vector<short> data;
        try {
            data = decoder(buff);
        } catch (std::runtime_error& err) {
            std::cout << buff << " - " << err.what();
            database.clear();
            musicNames.clear();
            return;
        }

        std::vector<uint64_t> hashes = calculateHashes(data);
        std::filesystem::path p(buff);
        uint32_t musicId = musicNames.size();
        musicNames.emplace_back(p.filename());
        for (uint32_t i = 0; i < hashes.size(); ++i) {
            database[hashes[i]].emplace_back(i, musicId);
        }
    }
}

void Database::loadFromIndexFile(const std::string &filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cout << filename << " - File open error\n";
        return;
    }
    size_t musicNamesNumber, databaseEntryNumber;
    fin >> musicNamesNumber >> databaseEntryNumber;
    char devnull;
    for (size_t i = 0; i < musicNamesNumber; ++i) {
        size_t musicNameSize;
        fin >> musicNameSize;
        char musicName[FILENAME_LIMIT_SIZE];
        musicName[musicNameSize] = '\0';
        fin.read(&devnull, 1);
        fin.read(musicName, musicNameSize);
        musicNames.push_back(std::string(musicName));
    }
    for (size_t i = 0; i < databaseEntryNumber; ++i) {
        uint64_t hashValue, vectorSize;
        fin >> hashValue >> vectorSize;
        for (size_t j = 0; j < vectorSize; ++j) {
            uint32_t timeBlock, musicId;
            fin >> timeBlock >> musicId;
            database[hashValue].emplace_back(timeBlock, musicId);
        }
    }
}

void Database::saveToFile(const std::string &filename) {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        std::cout << filename << " - File open error\n";
        return;
    }

    fout << musicNames.size() << " " << database.size() << "\n";
    for (const auto & musicName : musicNames) {
        fout << musicName.size() << " " << musicName << "\n";
    }
    for (const auto & pair : database) {
        fout << pair.first << " " << pair.second.size();
        for (const auto & entry : pair.second) {
            fout << " " << entry.timeBlock << " " << entry.musicId;
        }
        fout << "\n";
    }
}

std::vector<Entry> Database::findEntry(uint64_t hash) {
    auto it = database.find(hash);
    if (it == database.end())
        return {};
    return it->second;
}

std::string Database::getMusic(uint32_t musicId) {
    return musicNames[musicId];
}
