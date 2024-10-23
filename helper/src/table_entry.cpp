#include "table_entry.hpp"

std::vector<table_entry> get_table_entries()
{
    // Sample data
    std::vector<table_entry> data = {
        {"Alice Johnson", true, 23, 5.6f, 130.5, "New York", 1001},
        {"Bob Smith", false, 34, 5.8f, 180.0, "Los Angeles", 1002},
        {"Charlie Brown", true, 45, 6.0f, 200.5, "Chicago", 1003},
        {"Diana Prince", true, 30, 5.5f, 125.0, "Miami", 1004},
        {"Edward Elric", false, 29, 5.7f, 150.3, "Houston", 1005},
        {"Fiona Glenanne", true, 27, 5.4f, 115.0, "Seattle", 1006},
        {"George Lucas", true, 40, 6.2f, 210.0, "San Francisco", 1007},
        {"Hannah Baker", false, 35, 5.9f, 160.0, "Boston", 1008},
        {"Ian Fleming", true, 31, 6.1f, 190.0, "Atlanta", 1009},
        {"Jasmine Patel", true, 22, 5.3f, 110.0, "Phoenix", 1010}
    };
    return data;
}