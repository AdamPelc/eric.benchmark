#include "cout_redirect.hpp"

#include <benchmark/benchmark.h>
#include <format>
#include <iostream>
#include <random>
#include <sstream>

static void bm_format_int(benchmark::State& state) {
    std::ostringstream capture_stream;
    {
        std::mt19937 rng;
        const int value = rng();

        cout_redirect redirect(capture_stream);
        for (auto _ : state)
        {
            std::cout << std::format("Value={}", value);
        }
    }
    benchmark::DoNotOptimize(capture_stream.rdbuf());
}

BENCHMARK(bm_format_int);
