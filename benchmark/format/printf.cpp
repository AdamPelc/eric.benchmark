#include "cout_redirect.hpp"

#include <benchmark/benchmark.h>
#include <cstdio>
#include <random>
#include <sstream>

static void bm_printf_int(benchmark::State& state) {
    std::ostringstream capture_stream;
    {
        std::mt19937 rng;
        const int value = rng();

        cout_redirect redirect(capture_stream);
        for (auto _ : state)
        {
           printf("Value=%i", value);
        }
    }
    benchmark::DoNotOptimize(capture_stream.rdbuf());
}

BENCHMARK(bm_printf_int);