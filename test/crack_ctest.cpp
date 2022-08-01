#include <filesystem>
#include <assert.h>
#include "../src/crack.cpp"
#include "../src/crack.h"
#include "../src/utils.cpp"


std::filesystem::path cwd = std::filesystem::current_path();
std::string projectpath = cwd.string();

void test_argon2id() {
    std::ifstream hashlist;
    std::string hashfile{"hashfile.txt"};
    hashlist.open(hashfile);

    std::unordered_set<std::string> hashes;
    std::cout << projectpath << "\n";
    if (!hashlist) {
        std::cerr << "No such file: " << hashfile << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(hashlist, line)) 
        hashes.insert(line);
    hashlist.close();

    crack(false, hashes, "potfile.txt", "id", "words.txt");

    std::ifstream results;
    results.open("potfile.txt");
    std::getline(results, line);
    std::cout << line << "\n";
    assert(line == "$argon2id$v=19$m=65536,t=3,p=4$xcTixen2NvzaM8Y8LcbP5A$q8lxXUpbk47W+NSiOO8VmDN0YND5YJXtDTpbDZfrjNQ:hello");
    assert(line != "$argon2id$v=19$m=65536,t=3,p=4$X5yxTkTQksmZm7T2YbBFpw$qSxtdGrODw493kGAgtV/1+1julgZDOUEraKQpveDHWY:password");
    std::getline(results, line);
    std::cout << line << "\n";
    assert(line == "$argon2id$v=19$m=65536,t=3,p=4$X5yxTkTQksmZm7T2YbBFpw$qSxtdGrODw493kGAgtV/1+1julgZDOUEraKQpveDHWY:password");
    assert(line != "$argon2id$v=19$m=65536,t=3,p=4$xcTixen2NvzaM8Y8LcbP5A$q8lxXUpbk47W+NSiOO8VmDN0YND5YJXtDTpbDZfrjNQ:hello");
}


int main(int argc, char* argv[]) {
    test_argon2id();
    return 0;

}