#include "cout_redirect.hpp"

#include <benchmark/benchmark.h>
#include <iostream>
#include <random>
#include <sstream>

static void bm_ostream_int(benchmark::State& state) {
    std::ostringstream capture_stream;
    {
        std::mt19937 rng;
        const int value = rng();

        cout_redirect redirect(capture_stream);
        for (auto _ : state)
        {
            std::cout << "Value=";
            std::cout << value;
            std::cout << '\n';
        }
    }
    benchmark::DoNotOptimize(capture_stream.rdbuf());
}

BENCHMARK(bm_ostream_int);