#include <iostream>
#include <chrono>
#include <map>
#include "patricia.hpp"

const std::string DURATION_PREFIX = "us";

struct CaseInsensitiveCmp {
    bool operator()(const std::string& str1, const std::string& str2) const {
        unsigned int min_len = std::min(str1.size(), str2.size());
        for(size_t i = 0; i < min_len; ++i){
            if (std::tolower(str1[i]) > std::tolower(str2[i])) {
                return false;
            } else if (std::tolower(str1[i]) < std::tolower(str2[i])) {
                return true;
            }
        }
        if (str1.size() > str2.size()) {
            return false;
        } else if (str1.size() < str2.size()){
            return true;
        } else {
            return false;
        }
    }
};


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    TPatricia *patricia = new TPatricia();
    std::map<std::string, uint64_t, CaseInsensitiveCmp> rbTree;
    std::string action;
    uint64_t insert_count = 0;
    uint64_t find_count = 0;
    uint64_t erase_count = 0;
    uint64_t patriciaInsertTime = 0;
    uint64_t rbInsertTime = 0;
    uint64_t patriciaFindTime = 0;
    uint64_t rbFindTime = 0;
    uint64_t patriciaEraseTime = 0;
    uint64_t rbEraseTime = 0;
    std::chrono::time_point<std::chrono::system_clock> startTs, endTs;
    while (std::cin >> action) {
        if (action == "+") {
            ++insert_count;
            std::string key;
            uint64_t value;
            std::cin >> key >> value;

            startTs = std::chrono::system_clock::now();
            try {
                patricia->Add(key, value);
            }
            catch (const std::exception &e) {}
            endTs = std::chrono::system_clock::now();
            patriciaInsertTime += std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs ).count();

            startTs = std::chrono::system_clock::now();
            rbTree.insert_or_assign(key, value);
            endTs = std::chrono::system_clock::now();
            rbInsertTime += std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs ).count();

        } else if (action == "-") {
            ++erase_count;
            std::string key;
            std::cin >> key;

            startTs = std::chrono::system_clock::now();
            try {
                patricia->Erase(key);
            }
            catch (const std::exception &e) {}
            endTs = std::chrono::system_clock::now();
            patriciaEraseTime += std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs ).count();

            startTs = std::chrono::system_clock::now();
            rbTree.erase(key);
            endTs = std::chrono::system_clock::now();
            rbEraseTime += std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs ).count();

        } else {
            ++find_count;

            startTs = std::chrono::system_clock::now();
            try {
                patricia->At(action);
            }
            catch (const std::exception &e) {}
            endTs = std::chrono::system_clock::now();
            patriciaFindTime += std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs ).count();

            startTs = std::chrono::system_clock::now();
            try {
                rbTree.at(action);
            }
            catch (const std::exception &e) {}
            endTs = std::chrono::system_clock::now();
            rbFindTime += std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs ).count();
        }
    }

    std::cout << "Count of actions: " << insert_count + find_count + erase_count << "\n-----\n";
    std::cout << "Count of insert: " << insert_count << '\n';
    std::cout << "Patricia insert time: " << patriciaInsertTime << DURATION_PREFIX << '\n';
    std::cout << "STL map insert time: " << rbInsertTime << DURATION_PREFIX << "\n-----\n";
    std::cout << "Count of find: " << find_count << '\n';
    std::cout << "Patricia find time: " << patriciaFindTime << DURATION_PREFIX << '\n';
    std::cout << "STL map find time: " << rbFindTime << DURATION_PREFIX << "\n-----\n";
    std::cout << "Count of erase: " << erase_count << '\n';
    std::cout << "Patricia erase time: " << patriciaEraseTime << DURATION_PREFIX << '\n';
    std::cout << "STL map erase time: " << rbEraseTime << DURATION_PREFIX << "\n-----\n";
    std::cout << "Sum Patricia time: " << patriciaInsertTime + patriciaEraseTime + patriciaFindTime << DURATION_PREFIX << '\n';
    std::cout << "Sum STL map time: " << rbInsertTime + rbEraseTime + rbFindTime << DURATION_PREFIX << '\n';
}