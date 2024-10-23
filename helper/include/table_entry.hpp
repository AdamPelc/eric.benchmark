#pragma once

#include <vector>
#include <string>
#include <cstdint>

struct table_entry
{
  std::string name;
  bool is_valid;
  int age;
  float height;
  double weight;
  std::string city;
  uint64_t unique_id;
};


[[nodiscard]] std::vector<table_entry> get_table_entries();
