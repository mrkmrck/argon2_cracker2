#include "benchmark.h"


void run_benchmark() {

    #if 1
    unsigned char out[HASHLEN];
    unsigned char salt_array[SALTLEN];

    const uint32_t t_cost{3};            // iterations
    const uint32_t m_cost{(1<<16)};      // 64 mebibytes memory usage
    const uint32_t parallelism{4};       
    constexpr std::array<argon2_type, 3> types = {Argon2_d, Argon2_i, Argon2_id};

    const size_t iterations{1000};
    std::cout << "Total iterations: " << iterations << "\n";

    for (const auto &type : types) {

        double cpu_time{0.0};

        const auto start = std::chrono::system_clock::now();
        const std::clock_t c_start = std::clock();
 
        for (size_t i = 0; i < iterations; i++) {
            std::string pwd = std::to_string(i);
            size_t pwdlen = pwd.size();
            argon2_hash(t_cost, m_cost, parallelism, &pwd, pwdlen,
                        &salt_array, SALTLEN, &out, HASHLEN, NULL, 0, type,
                        ARGON2_VERSION_NUMBER);
        }


        const std::chrono::duration<double> run_time = std::chrono::system_clock::now() - start;
        const std::clock_t c_end = std::clock();

        cpu_time += (c_end-c_start) / (double)CLOCKS_PER_SEC;

        std::cout << argon2_type2string(type, 1) << " (" 
                  << t_cost << " iterations, " 
                  << m_cost << " MiB, " 
                  << parallelism << " threads):    "
                  << run_time.count() << " s  " 
                  << (double)iterations/run_time.count() << " H/s (run time)    " 
                  << cpu_time << " s  " 
                  << (double)iterations/cpu_time << " H/s (CPU time)    " 
                //   << "\n";
                  << std::endl;
    
    #endif
    }
}


