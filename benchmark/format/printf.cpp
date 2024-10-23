#include "cout_redirect.hpp"

#include <benchmark/benchmark.h>
#include <cstdio>
#include <random>
#include <sstream>

static void bm_printf_int(benchmark::State& state) {
    {
        std::mt19937 rng;
        const int value = rng();
        cout_redirect redirect{};
        for (auto _ : state)
        {
           printf("Value=%i", value);
        }
    }
}
BENCHMARK(bm_printf_int);
