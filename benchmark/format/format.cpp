#include "cout_redirect.hpp"
#include "table_entry.hpp"

#include <benchmark/benchmark.h>
#include <format>
#include <iostream>
#include <random>
#include <sstream>

template <std::integral T>
void bm_format_single_type(benchmark::State& state)
{
    std::mt19937 rng;
    std::uniform_int_distribution distribution(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    const T value = distribution(rng);

    cout_redirect redirect{};
    for (auto _ : state)
    {
        std::cout << std::format("Value={}", value);
    }
}
BENCHMARK(bm_format_single_type<int8_t>);
BENCHMARK(bm_format_single_type<uint8_t>);
BENCHMARK(bm_format_single_type<int16_t>);
BENCHMARK(bm_format_single_type<uint16_t>);
BENCHMARK(bm_format_single_type<int32_t>);
BENCHMARK(bm_format_single_type<uint32_t>);
BENCHMARK(bm_format_single_type<int64_t>);
BENCHMARK(bm_format_single_type<uint64_t>);

void bm_format_single_type_float(benchmark::State& state)
{
    std::mt19937 rng;
    std::uniform_real_distribution distribution(0.0f, 1.0f);
    const float value = distribution(rng);

    cout_redirect redirect{};
    for (auto _ : state)
    {
        std::cout << std::format("Value={}", value);
    }
}
BENCHMARK(bm_format_single_type_float);

void bm_format_single_type_double(benchmark::State& state)
{
    std::mt19937 rng;
    std::uniform_real_distribution distribution(0.0, 1.0);
    const double value = distribution(rng);

    cout_redirect redirect{};
    for (auto _ : state)
    {
        std::cout << std::format("Value={}", value);
    }
}
BENCHMARK(bm_format_single_type_double);

template <typename T>
void bm_format_single_type_string(benchmark::State& state)
{
    const auto value = T{"Lorem ipsum odor amet, consectetuer adipiscing elit. Integer vivamus dictumst lorem magna montes pellentesque semper ultricies hac. Aliquam justo donec convallis pulvinar lacinia massa. Lacus lectus vulputate rhoncus lectus quisque odio. Sapien tempor condimentum nascetur; platea rhoncus auctor tempor. Tortor ante tincidunt sodales purus aliquet donec varius ultrices. Sem sodales fusce ac netus; accumsan litora sagittis viverra. Vestibulum lacus quis lobortis aliquet potenti."};
    cout_redirect redirect{};
    for (auto _ : state)
    {
        std::cout << std::format("Value={}", value);
    }
}
BENCHMARK(bm_format_single_type_string<std::string>);
BENCHMARK(bm_format_single_type_string<std::string_view>);

static void bm_format_complex_table([[maybe_unused]] benchmark::State& state)
{
    const auto table_entries = get_table_entries();

    cout_redirect redirect{};
    for(auto _ : state)
    {
        std::cout << std::format("{:<15} {:<10} {:<5} {:<10} {:<10} {:<15} {:<15}\n", "Name", "Valid", "Age", "Height", "Weight", "City", "Unique ID");
        std::cout << std::format("{:-^80}\n", '-');
        for (const auto &[name, is_valid, age, height, weight, city, unique_id] : table_entries)
        {
            std::cout << std::format("{:<15} {:<#10b} {:<5} {:<10.2f} {:<10.2f} {:<15} {:<15}\n", name, is_valid, age, height, weight, city, unique_id);
        }
    }
}
BENCHMARK(bm_format_complex_table);


