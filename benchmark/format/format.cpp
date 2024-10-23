#include "cout_redirect.hpp"

#include <benchmark/benchmark.h>
#include <format>
#include <iostream>
#include <random>
#include <sstream>

static void bm_format_int(benchmark::State& state) {
    {
        std::mt19937 rng;
        const int value = rng();

        cout_redirect redirect{};
        for (auto _ : state)
        {
            std::cout << std::format("Value={}", value);
        }
    }
}

BENCHMARK(bm_format_int);
