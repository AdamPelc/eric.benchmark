#include "cout_redirect.hpp"

#include <benchmark/benchmark.h>
#include <iostream>
#include <random>
#include <sstream>

static void bm_ostream_int(benchmark::State& state) {
    {
        std::mt19937 rng;
        const int value = rng();

        cout_redirect redirect{};
        for (auto _ : state)
        {
            std::ostringstream os;
            os << "Value=";
            os << value;
            os << '\n';

            std::cout << os.str();
        }
    }
}

BENCHMARK(bm_ostream_int);