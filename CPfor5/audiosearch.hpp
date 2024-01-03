#ifndef CPFOR5_AUDIOSEARCH_HPP
#define CPFOR5_AUDIOSEARCH_HPP

#include "database.hpp"

class Audiosearch {
private:
    Database *db;
public:
    explicit Audiosearch(Database *db) : db(db) {};
    std::string search(const std::string& filename);
};


#endif //CPFOR5_AUDIOSEARCH_HPP
