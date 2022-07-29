#include "argon2.h"
#include "utils.h"

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_set>


void crack(const bool &format_hex, std::unordered_set<std::string> &hashes, const std::string &potfile, const std::string &stype, const std::string &wordfile);
void crack_using_stdin(const bool &format_hex, std::unordered_set<std::string> &hashes, const std::string &potfile, const argon2_type &type);
void crack_using_wordfile(const bool &format_hex, std::unordered_set<std::string> &hashes, const std::string &potfile, const argon2_type &type, const std::string &wordfile); 
size_t check_pwd(const bool &format_hex, std::unordered_set<std::string> &hashes, std::ostream &os, const std::string &pwd, const argon2_type &type);

