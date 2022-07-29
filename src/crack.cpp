#include "crack.h"

void crack(const bool &format_hex, std::unordered_set<std::string> &hashes, const std::string &potfile, const std::string &stype, const std::string &wordfile) {
    argon2_type type{Argon2_id};
    if (stype == "i")
        type = Argon2_i;
    else if (stype == "d")
        type = Argon2_d;
    
    if (potfile.size() > 0) 
        check_potfile(potfile, hashes);
            
    if (wordfile.size() > 0) 
        crack_using_wordfile(format_hex, hashes, potfile, type, wordfile);
    else
        crack_using_stdin(format_hex, hashes, potfile, type);
}   

void crack_using_wordfile(const bool &format_hex, std::unordered_set<std::string> &hashes, const std::string &potfile, const argon2_type &type, const std::string &wordfile) {
    auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << "Started on " << ctime(&timenow) << "\n";
    std::ifstream wordlist;
    wordlist.open(wordfile);
    if (!wordlist) {
        std::cerr << "No such file: " << wordfile << "\n";
        exit(1);
    } 

    std::string pwd;
    const auto start = std::chrono::system_clock::now();
    constexpr size_t notification_time{600};
    auto last = start;
    
    while (std::getline(wordlist, pwd)) {
        if (potfile.size() > 0) {
            const auto now = std::chrono::system_clock::now();
            const std::chrono::duration<double> elapsed = now - last;
            if (elapsed.count() > notification_time) {
                check_potfile(potfile, hashes);
                std::cout << "Time elapsed since last notification: " << elapsed.count() << "s \n";
                last = now; 
            }
            std::ofstream outfile;
            outfile.open(potfile, std::ios_base::app);
            check_pwd(format_hex, hashes, outfile, pwd, type);
            outfile.close();
        } else {
            check_pwd(format_hex, hashes, std::cout, pwd, type);
        }
    }
    wordlist.close();
    const std::chrono::duration<double> run_time = std::chrono::system_clock::now() - start;
    std::cout << "\nElapsed time: " << run_time.count() << "s \n";

    timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << "\nFinished on " << ctime(&timenow);
}

void crack_using_stdin(const bool &format_hex, std::unordered_set<std::string> &hashes, const std::string &potfile, const argon2_type &type) {
    while (true) {
        std::string pwd;
        printf("\nEnter word:\n");
        std::cin >> pwd;
        std::cout << "Checking hashes for password: " << pwd << "\n";

        constexpr size_t notification_time{6};
        const auto start = std::chrono::system_clock::now();
        auto last = start;
        if (potfile.size() > 0) {
            const auto now = std::chrono::system_clock::now();
            const std::chrono::duration<double> elapsed = now - last;
            if (elapsed.count() > notification_time) {
                check_potfile(potfile, hashes);
                std::cout << "Time elapsed since last notification: " << elapsed.count() << "s \n";
                last = now; 
            }
            std::ofstream outfile;
            outfile.open(potfile, std::ios_base::app);
            auto nfound = check_pwd(format_hex, hashes, outfile, pwd, type);
            std::cout << nfound << " hash(es) found\n";
            outfile.close();
        } else {
            check_pwd(format_hex, hashes, std::cout, pwd, type);
        }
        const std::chrono::duration<double> run_time = std::chrono::system_clock::now() - start;
        std::cout << "Elapsed time: " << run_time.count() << "s \n";
    }
}

size_t check_pwd(const bool &format_hex, std::unordered_set<std::string> &hashes, std::ostream &os, const std::string &pwd, const argon2_type &type) {
    size_t nfound{0};

    auto verify = [format_hex, &os, pwd, type](auto const& hash) { 
        if (argon2_verify(hash.c_str(), pwd.c_str(), pwd.size(), type) == 0) {
            os << hash << ":";
            if (format_hex) 
                print_hex(os, pwd);
            else
                os << pwd;
            os << "\n";
            return true;
        } 
        return false; };
    nfound += std::erase_if(hashes, verify);
    return nfound;
}
