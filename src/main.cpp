#include "benchmark.h"
#include "crack.h"
#include <filesystem>

#include <cxx_argp_parser.h>


std::filesystem::path cwd = std::filesystem::current_path();
std::string projectpath = cwd.string();


// helper for basic variable-based options
class argparser {
	cxx_argp::parser parser_;

public:
    struct {
        bool benchmark{false};
        bool enable = false;
        std::string hashfile{};
        std::string potfile{};
        std::string wordlist{};
        std::string type{"id"};
        bool format_hex{false};
    } args;

	argparser(ssize_t count = 0)
	    : parser_(count) {
        parser_.add_option({"benchmark", 'b', nullptr, 0, "Run benchmark."}, args.benchmark);
	    parser_.add_option({"hashfile", 'h', "HASHFILE", 0, "Path to file with the hash values."}, args.hashfile);
	    parser_.add_option({"potfile", 'p', "POTFILE", 0, "Path to potfile for found solutions."}, args.potfile);
	    parser_.add_option({"type", 't', "ARGON2_TYPE", 0, "Choose argon2 type (id, i, or d) [default: id]."}, args.type);
	    parser_.add_option({"wordlist", 'w', "WORDLIST", 0, "Path to wordlist file [default: stdin]."}, args.wordlist);
	    parser_.add_option({"format-hex", 'x', nullptr, 0, "Store solutions in HEX format."}, args.format_hex);
	}

	bool parse(int argc, char *argv[]) {
		return parser_.parse(argc, argv);
	}

	const std::vector<std::string> &arguments() const { return parser_.arguments(); }
};


int main(int argc, char **argv) {
   
    argparser ap;

    ap.parse(argc, argv);

    if (ap.args.benchmark) {
        std::cout << "Running benchmark.\n";
        run_benchmark();
        exit(0);
    }

    std::ifstream hashlist;
    hashlist.open(ap.args.hashfile);

    std::unordered_set<std::string> hashes;
    if (!hashlist) {
        std::cerr << "No such file: " << ap.args.hashfile << "\n";
        exit(1);
    } else {
        std::cout << "Hashfile: " << ap.args.hashfile << "\n";
        std::string line;
        while (std::getline(hashlist, line)) 
            hashes.insert(line);
        hashlist.close();
    }

    if (ap.args.wordlist.size() > 0) {
        std::ifstream wordlist;
        wordlist.open(ap.args.wordlist);
        if (!wordlist) {
            std::cerr << "No such file: " << ap.args.wordlist << "\n";
            exit(1);
        }
        std::cout << "Wordlist: " << ap.args.wordlist << "\n\n";
    }

    crack(ap.args.format_hex, hashes, ap.args.potfile, ap.args.type, ap.args.wordlist);
    
    return 0;
}