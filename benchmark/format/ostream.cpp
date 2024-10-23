#include "cout_redirect.hpp"

#include <benchmark/benchmark.h>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <table_entry.hpp>

template <std::integral T>
void bm_oss_single_int(benchmark::State& state)
{
    std::mt19937 rng;
    std::uniform_int_distribution distribution(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    const T value = distribution(rng);

    cout_redirect redirect{};
    for (auto _ : state)
    {
        std::ostringstream oss;
        oss << "Value=";
        oss << value;

        std::cout << oss.str();
    }
}
BENCHMARK(bm_oss_single_int<int8_t>);
BENCHMARK(bm_oss_single_int<uint8_t>);
BENCHMARK(bm_oss_single_int<int16_t>);
BENCHMARK(bm_oss_single_int<uint16_t>);
BENCHMARK(bm_oss_single_int<int32_t>);
BENCHMARK(bm_oss_single_int<uint32_t>);
BENCHMARK(bm_oss_single_int<int64_t>);
BENCHMARK(bm_oss_single_int<uint64_t>);

template <std::floating_point T>
void bm_oss_single_float(benchmark::State& state)
{
    std::mt19937 rng;
    std::uniform_real_distribution<T> distribution(0.0, 1.0);
    const float value = distribution(rng);

    cout_redirect redirect{};
    for (auto _ : state)
    {
        std::ostringstream oss;
        oss << "Value=";
        oss << value;

        std::cout << oss.str();
    }
}
BENCHMARK(bm_oss_single_float<float>);
BENCHMARK(bm_oss_single_float<double>);

template <typename T>
void bm_oss_single_type_string(benchmark::State& state)
{
    const auto value = T{"Lorem ipsum odor amet, consectetuer adipiscing elit. Integer vivamus dictumst lorem magna montes pellentesque semper ultricies hac. Aliquam justo donec convallis pulvinar lacinia massa. Lacus lectus vulputate rhoncus lectus quisque odio. Sapien tempor condimentum nascetur; platea rhoncus auctor tempor. Tortor ante tincidunt sodales purus aliquet donec varius ultrices. Sem sodales fusce ac netus; accumsan litora sagittis viverra. Vestibulum lacus quis lobortis aliquet potenti."};
    cout_redirect redirect{};
    for (auto _ : state)
    {
        std::ostringstream oss;
        oss << "Value=";
        oss << value;

        std::cout << oss.str();
    }
}
BENCHMARK(bm_oss_single_type_string<std::string>);
BENCHMARK(bm_oss_single_type_string<std::string_view>);

static void bm_oss_complex_table(benchmark::State& state)
{
    const auto table_entries = get_table_entries();

    cout_redirect redirect{};
    for(auto _ : state)
    {
        // Create an output string stream
        std::ostringstream oss;

        // Print the header
        oss << std::left
            << std::setw(15) << "Name"
            << std::setw(10) << "Valid"
            << std::setw(5)  << "Age"
            << std::setw(10) << "Height"
            << std::setw(10) << "Weight"
            << std::setw(15) << "City"
            << std::setw(15) << "Unique ID"
            << '\n';

        // Print the table entries
        for (const auto& entry : table_entries) {
            // Convert is_valid to binary representation with 0b prefix
            std::string is_valid_str = entry.is_valid ? "0b1" : "0b0";

            oss << std::left
                << std::setw(15) << entry.name
                << std::setw(10) << is_valid_str
                << std::setw(5)  << entry.age
                << std::setw(10) << std::fixed << std::setprecision(2) << entry.height
                << std::setw(10) << std::fixed << std::setprecision(2) << entry.weight
                << std::setw(15) << entry.city
                << std::setw(15) << entry.unique_id
                << '\n';
        }

        // Output the formatted table
        std::cout << oss.str();
    }
}
BENCHMARK(bm_oss_complex_table)->Unit(benchmark::kMicrosecond);