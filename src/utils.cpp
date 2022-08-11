#include "utils.h"


void print_hex(std::ostream &os, const std::string &s) {
    for (size_t i = 0; i < s.size(); i++)
        os << std::hex << int(s[i]);
}


void check_potfile(const std::string &file, std::unordered_set<std::string> &hashes) {
    size_t nfound{0};
    std::cout << "Checking potfile...\n";
    std::ifstream potfile; 
    potfile.open(file);
    std::string line;
    while (std::getline(potfile, line)) {       
        std::istringstream iss(line);
        while (std::getline(iss, line, ':')) {
                nfound += std::erase_if(hashes, [line, &nfound](auto const& hash) {
                return (line == hash);
            });
        }
    }
    std::cout << nfound << " (new) hash(es) found in potfile.\n" << std::endl;

    potfile.close();
}
