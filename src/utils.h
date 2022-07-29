
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>


void print_hex(std::ostream &os, const std::string &s);

void check_potfile(const std::string &file, std::unordered_set<std::string> &hashes);