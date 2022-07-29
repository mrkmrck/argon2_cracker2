#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "utils.h"
#include "argon2.h"
#include <iostream>
#include <string>
#include <array>
#include <chrono>

#define HASHLEN 32
#define SALTLEN 16

void run_benchmark();

#endif // BENCHMARK_H