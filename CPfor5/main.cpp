#include <iostream>
#include <fstream>

#include "database.hpp"
#include "audiosearch.hpp"

void printUsage(const std::string& programName) {
    std::cout << "usage:\n\t" << programName << " index --input <input file> --output <index file>\n\t"
     << programName << " search --index <index file> --input <input file> --output <output file>\n";
}

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    if (argc != 6 && argc != 8) {
        printUsage(argv[0]);
        return 0;
    }
    std::string command(argv[1]), inputFile, indexFile, outputFile;

    if (command != "index" && command != "search") {
        std::cout << "Wrong command " << command << "\n";
        return 0;
    }
    for (size_t i = 2; i < argc; i+=2) {
        std::string flag(argv[i]), value(argv[i+1]);
        if (flag == "--index")
            indexFile = value;
        else if (flag == "--input")
            inputFile = value;
        else if (flag == "--output")
            outputFile = value;
        else {
            std::cout << "Wrong parameter " << flag << "\n";
            return 0;
        }
    }

    Database *db = new Database();
    if (command == "index") {
        db->loadFromNamesFile(inputFile);
        db->saveToFile(outputFile);
        std::cout << "OK\n";
    } else {
        db->loadFromIndexFile(indexFile);
        Audiosearch audiosearch(db);

        std::ifstream fin(inputFile);
        std::ofstream fout(outputFile);
        if (!fin.is_open())
            std::cout << inputFile << " - File open error\n";
        else if (!fout.is_open())
            std::cout << outputFile << " - File open error\n";

        char buff[FILENAME_LIMIT_SIZE];
        while (!fin.eof()) {
            fin.getline(buff, FILENAME_LIMIT_SIZE);
            if (buff[0] == '\0')
                break;
            std::string answer = audiosearch.search(std::string(buff));
            fout.write(answer.data(), answer.size());
        }
    }

    return 0;
}
