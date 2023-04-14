#include <iostream>
#include <algorithm>
#include "patricia.hpp"
#include "custom_exception.hpp"

int main() {
    TPatricia *tree = new TPatricia();
    std::string action;
    while (std::cin >> action) {
        try {
            if (action == "+") {
                std::string key;
                uint64_t value;
                std::cin >> key >> value;
                tree->Add(key, value);
                std::cout << "OK\n";
            } else if (action == "-") {
                std::string key;
                std::cin >> key;
                tree->Erase(key);
                std::cout << "OK\n";
            } else if (action == "!") {
                std::string action2;
                std::string path;
                std::cin >> action2 >> path;
                if (action2 == "Save") {
                    tree->Save(path);
                } else {
                    TPatricia *new_tree = new TPatricia();
                    new_tree->Load(path);
                    delete tree;
                    tree = new_tree;
                }
                std::cout << "OK\n";
            } else {
                uint64_t value = tree->At(action);
                std::cout << "OK: " << value << '\n';
            }
        }
        catch (const TKeyAlreadyExists &e) {
            std::cout << e.what() << '\n';
        }
        catch (const TNoSuchKey &e) {
            std::cout << e.what() << '\n';
        }
        catch (const std::exception &e) {
            std::cout << "Error: " << e.what() << '\n';
        }
    }
    delete tree;
    return 0;
}
