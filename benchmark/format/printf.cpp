#include "cout_redirect.hpp"

#include <benchmark/benchmark.h>
#include <cstdio>
#include <random>
#include <sstream>
#include <table_entry.hpp>

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

template <std::integral T>
static void bm_printf_single_int(benchmark::State& state)
{
    std::mt19937 rng;
    std::uniform_int_distribution distribution(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    const T value = distribution(rng);

    cout_redirect redirect{};
    for (auto _ : state)
    {
        printf("Value=%i", value);
    }
}
BENCHMARK(bm_printf_single_int<int8_t>);
BENCHMARK(bm_printf_single_int<int16_t>);
BENCHMARK(bm_printf_single_int<int32_t>);

static void bm_printf_single_int64(benchmark::State& state)
{
    std::mt19937 rng;
    std::uniform_int_distribution distribution(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max());
    const int64_t value = distribution(rng);

    cout_redirect redirect{};
    for (auto _ : state)
    {
        printf("Value=%li", value);
    }
}
BENCHMARK(bm_printf_single_int64);

template <std::integral T>
static void bm_printf_single_uint(benchmark::State& state)
{
    std::mt19937 rng;
    std::uniform_int_distribution distribution(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    const T value = distribution(rng);

    cout_redirect redirect{};
    for (auto _ : state)
    {
        printf("Value=%u", value);
    }
}
BENCHMARK(bm_printf_single_uint<uint8_t>);
BENCHMARK(bm_printf_single_uint<uint16_t>);
BENCHMARK(bm_printf_single_uint<uint32_t>);

static void bm_printf_single_uint64(benchmark::State& state)
{
    std::mt19937 rng;
    std::uniform_int_distribution distribution(std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max());
    const uint64_t value = distribution(rng);

    cout_redirect redirect{};
    for (auto _ : state)
    {
        printf("Value=%lul", value);
    }
}
BENCHMARK(bm_printf_single_uint64);

template <std::floating_point T>
static void bm_printf_single_float(benchmark::State& state)
{
    std::mt19937 rng;
    std::uniform_real_distribution<T> distribution(0.0, 1.0);
    const float value = distribution(rng);

    cout_redirect redirect{};
    for (auto _ : state)
    {
        printf("Value=%f", value);
    }
}
BENCHMARK(bm_printf_single_float<float>);
BENCHMARK(bm_printf_single_float<double>);

template <typename T>
void bm_printf_single_type_string(benchmark::State& state)
{
    const auto value = T{"Lorem ipsum odor amet, consectetuer adipiscing elit. Integer vivamus dictumst lorem magna montes pellentesque semper ultricies hac. Aliquam justo donec convallis pulvinar lacinia massa. Lacus lectus vulputate rhoncus lectus quisque odio. Sapien tempor condimentum nascetur; platea rhoncus auctor tempor. Tortor ante tincidunt sodales purus aliquet donec varius ultrices. Sem sodales fusce ac netus; accumsan litora sagittis viverra. Vestibulum lacus quis lobortis aliquet potenti."};
    cout_redirect redirect{};
    for (auto _ : state)
    {
        printf("Value=%s", value.data());
    }
}
BENCHMARK(bm_printf_single_type_string<std::string>);
BENCHMARK(bm_printf_single_type_string<std::string_view>);

static void bm_format_complex_table([[maybe_unused]] benchmark::State& state)
{
    const auto table_entries = get_table_entries();

    cout_redirect redirect{};
    for(auto _ : state)
    {
        // Print the header
        printf("%-15s %-10s %-5s %-10s %-10s %-15s %-15s\n",
               "Name", "Valid", "Age", "Height", "Weight", "City", "Unique ID");

        // Print the table entries
        for (const auto &[name, is_valid, age, height, weight, city, unique_id] : table_entries) {
            // Convert is_valid to binary representation with 0b prefix
            const char* is_valid_str = is_valid ? "0b1" : "0b0";

            // Print each row
            printf("%-15s %-10s %-5d %-10.2f %-10.2f %-15s %-15llu\n",
                   name.c_str(),
                   is_valid_str,
                   age,
                   height,
                   weight,
                   city.c_str(),
                   static_cast<unsigned long long>(unique_id));
        }
    }
}
BENCHMARK(bm_format_complex_table)->Unit(benchmark::kMicrosecond);